#include "DeathState.hpp"

DeathState::DeathState(Engine& engine, std::string level) :
_engine(engine), _window(engine.window)
{
	_music = _engine.sound.play2D(ASSET_PATH "sounds/game_over.wav", true, false, true);
	auto e = _registry.create();
	_registry.assign<c::EngineTag>(entt::tag_t{}, e, engine);

	auto entity = _registry.create();

	_registry.assign<c::Button>(entity,
		scripts::switch_level(level)
	);

	_registry.assign<c::Image>(entity,
		"assets/textures/death.png"
	);
}

DeathState::~DeathState(void) {
	if (_music)
		_music->stop();
}

void	DeathState::Update(double dt)
{
	systems::Buttons(_registry, _window);
	systems::Images(_registry, _imageCache, _window);
}
