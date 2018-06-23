#include "PauseState.hpp"
#include "components.hpp"
#include "MenuState.hpp"
#include "systems.hpp"
#include "SettingState.hpp"

PauseState::PauseState(Engine& e) :
_engine(e), _window(e.window)
{
//create pause background
	auto background = _registry.create();
	_registry.assign<c::Image>(background, "assets/textures/menu.png");

//create resume button
	auto resumeButton = _registry.create();
	auto resumeEvent = [this](entt::DefaultRegistry&, uint32_t)
	{
		_engine.PopState();
	};
	_registry.assign<c::Button>(resumeButton,
				    resumeEvent,
				    glm::vec2(-0.1, -0.8),
				    glm::vec2(0.1, -0.6));
	_registry.assign<c::Image>(resumeButton,
				   "assets/textures/blue_button.png",
				   glm::vec2(-0.1, -0.8),
				   glm::vec2(0.1, -0.6),
				   1);
	_registry.assign<c::Text>(resumeButton,
				  "Resume Game",
				  glm::vec2(-0.1, -0.8),
				  glm::vec2(0.1, -0.6));

//create back to main menu button
	auto menuButton = _registry.create();
	auto menuEvent = [this](entt::DefaultRegistry&, uint32_t)
	{
		_engine.PopState();
		_engine.PopState();
	};
	_registry.assign<c::Button>(menuButton,
				    menuEvent,
				    glm::vec2(-0.1, -0.4),
				    glm::vec2(0.1, -0.2));
	_registry.assign<c::Image>(menuButton,
				   "assets/textures/blue_button.png",
				   glm::vec2(-0.1, -0.4),
				   glm::vec2(0.1, -0.2),
				   1);
	_registry.assign<c::Text>(menuButton,
				  "Back to Menu",
				  glm::vec2(-0.1, -0.4),
				  glm::vec2(0.1, -0.2));

//create a quit game button
	auto quitButton = _registry.create();
	auto quitEvent = [this](entt::DefaultRegistry&, uint32_t)
	{
		_engine.isRunning = false;
	};
	_registry.assign<c::Button>(quitButton,
				    quitEvent,
				    glm::vec2(-0.1, 0.2),
				    glm::vec2(0.1, 0.4));
	_registry.assign<c::Image>(quitButton,
				   "assets/textures/blue_button.png",
				   glm::vec2(-0.1, 0.2),
				   glm::vec2(0.1, 0.4),
				   1);
	_registry.assign<c::Text>(quitButton,
				  "  Quit  ",
				  glm::vec2(-0.1, 0.2),
				  glm::vec2(0.1, 0.4));

//create a settings option
	auto settingButton = _registry.create();
	auto settingEvent = [this](entt::DefaultRegistry&, uint32_t)
	{
		_engine.PushState(new SettingState(_engine));
	};
	_registry.assign<c::Button>(settingButton,
				    settingEvent,
				    glm::vec2(-0.1, 0.5),
				    glm::vec2(0.1, 0.7));
	_registry.assign<c::Image>(settingButton,
				   "assets/textures/blue_button.png",
				   glm::vec2(-0.1, 0.5),
				   glm::vec2(0.1, 0.7),
				   1);
	_registry.assign<c::Text>(settingButton,
				  "Settings",
				  glm::vec2(-0.1, 0.5),
				  glm::vec2(0.1, 0.7));
}

PauseState::~PauseState(void) {}

void	PauseState::Update(double)
{
	systems::Buttons(_registry, _window);
	systems::Images(_registry, _imageCache, _window);
	systems::Texts(_registry, _window);
}
