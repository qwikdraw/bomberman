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

	auto nextstate = [this](entt::DefaultRegistry& r, uint32_t e)
	{
		_engine.PushState(new GameState(_engine, "01"));
	};
	
	_registry.assign<c::Button>(entity,
				    nextstate,
				    glm::vec2(-0.1, -0.1),
				    glm::vec2(0.1, 0.1));

	_registry.assign<c::Image>(entity,
				   "assets/textures/blue_button.png",
				   glm::vec2(-0.1, -0.1),
				   glm::vec2(0.1, 0.1));

	_registry.assign<c::Text>(entity, "Start",
				  glm::vec2(-0.08, -0.08),
				  glm::vec2(0.08, 0.08));
	
	glClearColor(0.2, 0.25, 0.29, 1.0);

//creating settings button
	auto settingButton = _registry.create();
	auto settingState = [this](entt::DefaultRegistry& r, uint32_t e)
	{
		_engine.PushState(new SettingState(_engine));
	};
	_registry.assign<c::Button>(settingButton,
				    settingState,
				    glm::vec2(-0.1, -0.4),
				    glm::vec2(0.1, -0.2));
	_registry.assign<c::Image>(settingButton,
				   "assets/textures/blue_button.png",
				   glm::vec2(-0.1, -0.4),
				   glm::vec2(0.1, -0.2));
	_registry.assign<c::Text>(settingButton,
				  "Settings",
				  glm::vec2(-0.1, -0.4),
				  glm::vec2(0.1, -0.2));

//creating level select button
	auto levelSelect = _registry.create();
	auto selectState = [this](entt::DefaultRegistry& r, uint32_t e)
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
}

MenuState::~MenuState(void) {}

void MenuState::Update(double dt)
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
