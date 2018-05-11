#include "DeathState.hpp"

DeathState::DeathState(Engine& engine) :
_engine(engine), _window(engine.window)
{
	auto e = _registry.create();
	_registry.attach<c::EngineTag>(e, engine);

	auto entity = _registry.create();

	_registry.assign<c::Button>(entity,
		callbacks::change_state(_registry, StateType::Level1)
	);

	_registry.assign<c::Image>(entity,
		"assets/textures/metal_sheet.png"
	);
}

DeathState::~DeathState(void) {}

void	DeathState::Update(double dt)
{
	systems::Buttons(_registry, _window);
	systems::Images(_registry, _imageCache, _window);
}
