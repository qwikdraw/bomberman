#include "MenuState.hpp"
#include "TestState.hpp"
#include "components.hpp"
#include "bomberman.hpp"
#include "systems.hpp"
#include "Text.hpp"

namespace c = components;

MenuState::MenuState(Engine& e) :
_engine(e), _window(e.window)
{
	auto entity = _registry.create();	

	auto nextstate = [this](){
		_engine.PushState(new TestState(_engine));
	};
	
	_registry.assign<c::Button>(entity,
		"assets/textures/metal_sheet.png", "assets/textures/stone_floor.png",
		nextstate, glm::vec2(-0.1, -0.1), glm::vec2(0.1, 0.1), 0.1f);

	glClearColor(0.2, 0.25, 0.29, 1.0);
}

MenuState::~MenuState(void) {}

void MenuState::Update(double dt)
{
	Text t("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRZTUVWXYZ 1234567890");
	systems::Buttons(_registry, _imageCache, _window, dt);
	t.Render(_window.GetAspect());
}
