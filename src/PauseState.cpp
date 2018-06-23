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
				    glm::vec2(-0.15, -0.15),
				    glm::vec2(0.15, 0.15));
	_registry.assign<c::Image>(resumeButton,
				   "assets/textures/blue_button.png",
				   glm::vec2(-0.15, -0.15),
				   glm::vec2(0.15, 0.15),
				   1);
	_registry.assign<c::Text>(resumeButton,
				  " Resume ",
				  glm::vec2(-0.15, -0.15),
				  glm::vec2(0.15, 0.15));

//create back to main menu button
	auto menuButton = _registry.create();
	auto menuEvent = [this](entt::DefaultRegistry&, uint32_t)
	{
		_engine.PopState();
		_engine.PopState();
	};
	_registry.assign<c::Button>(menuButton,
				    menuEvent,
				    glm::vec2(-0.45, -0.6),
				    glm::vec2(-0.25, -0.4));
	_registry.assign<c::Image>(menuButton,
				   "assets/textures/blue_button.png",
				   glm::vec2(-0.45, -0.6),
				   glm::vec2(-0.25, -0.4),
				   1);
	_registry.assign<c::Text>(menuButton,
				  "Back to Menu",
				  glm::vec2(-0.45, -0.6),
				  glm::vec2(-0.25, -0.4));

//creating quit button
	auto quit = _registry.create();
	auto quitAction = [this](entt::DefaultRegistry&, uint32_t)
	{
		_engine.isRunning = false;
	};
	_registry.assign<c::Button>(quit, quitAction,
				    glm::vec2(-0.98, 0.9),
				    glm::vec2(-0.9, 0.98));
	_registry.assign<c::Image>(quit,
				  "assets/textures/dark_blue_button.png",
				  glm::vec2(-0.98, 0.9),
				   glm::vec2(-0.9, 0.98),
				   1);
	_registry.assign<c::Text>(quit, " Quit ",
				  glm::vec2(-0.98, 0.9),
				  glm::vec2(-0.9, 0.98));

//create a settings option
	auto settingButton = _registry.create();
	auto settingEvent = [this](entt::DefaultRegistry&, uint32_t)
	{
		_engine.PushState(new SettingState(_engine));
	};
	_registry.assign<c::Button>(settingButton,
				    settingEvent,
				    glm::vec2(0.25, -0.6),
				    glm::vec2(0.45, -0.4));
	_registry.assign<c::Image>(settingButton,
				   "assets/textures/blue_button.png",
				   glm::vec2(0.25, -0.6),
				   glm::vec2(0.45, -0.4),
				   1);
	_registry.assign<c::Text>(settingButton,
				  "Settings",
				  glm::vec2(0.25, -0.6),
				  glm::vec2(0.45, -0.4));
}

PauseState::~PauseState(void) {}

void	PauseState::Update(double)
{
	systems::Buttons(_registry, _window);
	systems::Images(_registry, _imageCache, _window);
	systems::Texts(_registry, _window);
}
