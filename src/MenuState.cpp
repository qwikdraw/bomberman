#include "MenuState.hpp"
#include "GameState.hpp"
#include "components.hpp"
#include "bomberman.hpp"
#include "systems.hpp"
#include "Text.hpp"
#include "SettingState.hpp"
#include "PauseState.hpp"
#include "LevelSelectState.hpp"

namespace c = components;

MenuState::MenuState(Engine& e) :
_engine(e), _window(e.window)
{
	auto entity = _registry.create();	
	_music = _engine.sound.play2D(ASSET_PATH "sounds/menu.wav", true, false, true);

	auto nextstate = [this](entt::DefaultRegistry&, uint32_t)
	{
		_engine.PushState(new GameState(_engine, "01"));
	};
	
	_registry.assign<c::Button>(entity,
				    nextstate,
				    glm::vec2(-0.15, -0.15),
				    glm::vec2(0.15, 0.15));

	_registry.assign<c::Image>(entity,
				   "assets/textures/blue_button.png",
				   glm::vec2(-0.15, -0.15),
				   glm::vec2(0.15, 0.15));

	_registry.assign<c::Text>(entity, " Start ",
				  glm::vec2(-0.15, -0.15),
				  glm::vec2(0.15, 0.15));
	
	glClearColor(0.2, 0.25, 0.29, 1.0);

//creating settings button
	auto settingButton = _registry.create();
	auto settingState = [this](entt::DefaultRegistry&, uint32_t)
	{
		_engine.PushState(new SettingState(_engine));
	};
	_registry.assign<c::Button>(settingButton,
				    settingState,
				    glm::vec2(-0.1, -0.5),
				    glm::vec2(0.1, -0.3));
	_registry.assign<c::Image>(settingButton,
				   "assets/textures/blue_button.png",
				   glm::vec2(-0.1, -0.5),
				   glm::vec2(0.1, -0.3));
	_registry.assign<c::Text>(settingButton,
				  "Settings",
				  glm::vec2(-0.1, -0.5),
				  glm::vec2(0.1, -0.3));

//creating level select button
	auto levelSelect = _registry.create();
	auto selectState = [this](entt::DefaultRegistry&, uint32_t)
	{
		_engine.PushState(new LevelSelectState(_engine));
	};
	_registry.assign<c::Button>(levelSelect,
				    selectState,
				    glm::vec2(-0.1, -0.8),
				    glm::vec2(0.1, -0.6));
	_registry.assign<c::Image>(levelSelect,
				   "assets/textures/blue_button.png",
				   glm::vec2(-0.1, -0.8),
				   glm::vec2(0.1, -0.6));
	_registry.assign<c::Text>(levelSelect,
				   "Level Select",
				   glm::vec2(-0.1, -0.8),
				   glm::vec2(0.1, -0.6));

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
				  glm::vec2(-0.9, 0.98));
	_registry.assign<c::Text>(quit, " Quit ",
				  glm::vec2(-0.98, 0.9),
				  glm::vec2(-0.9, 0.98));
	

//create background
	auto background	= _registry.create();
	_registry.assign<c::Image>(background, "assets/textures/menu.png",
				   glm::vec2(-1, -1),
				   glm::vec2(1, 1),
				   -1);
}

MenuState::~MenuState(void) {}

void MenuState::Update(double)
{
	if (_music && _music->isFinished())
	{
		_engine.sound.stopAllSounds();
		free(_music);
		_music = _engine.sound.play2D(ASSET_PATH "sounds/menu.wav", true, false, true);
	}
	systems::Buttons(_registry, _window);
	systems::Images(_registry, _imageCache, _window);
	systems::Texts(_registry, _window);
}
