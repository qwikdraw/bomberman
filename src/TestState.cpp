#include "TestState.hpp"
#include "components.hpp"
#include "bomberman.hpp"
#include "systems.hpp"

namespace c = components;

void	thing(void)
{
	std::cout << "this worked" << std::endl;
}

TestState::TestState(Engine& e) :
_engine(e), _window(e.window)
{
	_camera.Move(glm::vec3(-5, 0, 0));
	_lights.push_back(new Light(glm::vec3(0, 0, 3), glm::vec3(1, 1, 1), 10));

	auto entity = _registry.create();
	_registry.assign<c::Model>(entity, "block", glm::mat4(1));
	_registry.assign<c::Position>(entity, glm::vec3(0, 0, 0));
	_registry.assign<c::Decay>(entity, 50.0f);
	_registry.assign<c::Button>(entity,
		"assets/textures/the_man.png", "assets/textures/alpha_test2.png",
		thing, glm::vec2(0.7, 0.7), glm::vec2(0.8, 0.8), 0.1f);

	glClearColor(0.2, 0.25, 0.29, 1.0);
}

TestState::~TestState(void)
{
	for (auto l: _lights)
		delete l;
}

void TestState::Update(double dt)
{
	systems::RenderModels(_registry, _modelCache, _window, _camera);
	systems::Decay(_registry, dt);
	systems::Buttons(_registry, _imageCache, _window, dt);
}
