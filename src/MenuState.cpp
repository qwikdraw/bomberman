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

	auto nextstate = [this](entt::DefaultRegistry& r, uint32_t e)
	{
		_engine.PushState(new TestState(_engine));
	};
	
	_registry.assign<c::Button>(entity,
				    nextstate,
				    glm::vec2(-0.1, -0.1),
				    glm::vec2(0.1, 0.1));

	_registry.assign<c::Image>(entity,
				   "assets/textures/metal_sheet.png",
				   glm::vec2(-0.1, -0.1),
				   glm::vec2(0.1, 0.1));

	_registry.assign<c::Text>(entity, "Start",
				  glm::vec2(-0.08, -0.08),
				  glm::vec2(0.08, 0.08));
	
	glClearColor(0.2, 0.25, 0.29, 1.0);
}

MenuState::~MenuState(void) {}

void MenuState::Update(double dt)
{
	systems::Buttons(_registry, _window);
	systems::Images(_registry, _imageCache, _window);
	systems::Texts(_registry, _window);
}
