#include "MenuState.hpp"
#include "TestState.hpp"
#include "components.hpp"
#include "bomberman.hpp"
#include "systems.hpp"

namespace c = components;

MenuState::MenuState(Engine& e) :
_engine(e), _window(e.window)
{
	_camera.Move(glm::vec3(-5, 0, 0));
	_lights.push_back(new Light(glm::vec3(0, 0, 3), glm::vec3(1, 1, 1), 10));

	auto entity = _registry.create();	

	auto nextstate = [this](){
		_engine.ChangeState(new TestState(_engine));
	};
	
	_registry.assign<c::Button>(entity,
		"assets/textures/metal_sheet.png", "assets/textures/stone_floor.png",
		nextstate, glm::vec2(-0.1, -0.1), glm::vec2(0.1, 0.1), 0.1f);

	glClearColor(0.2, 0.25, 0.29, 1.0);
}

MenuState::~MenuState(void)
{
	for (auto l: _lights)
		delete l;
}

void MenuState::Update(double dt)
{
	systems::RenderModels(_registry, _modelCache, _window, _camera);
	systems::Decay(_registry, dt);
	systems::Buttons(_registry, _imageCache, _window, dt);
}
