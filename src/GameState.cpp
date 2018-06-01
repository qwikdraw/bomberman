#include "GameState.hpp"
#include "ParticleExplosion.hpp"
#include "build_level.hpp"
#include "PauseState.hpp"

GameState::GameState(Engine& e, std::string level) :
_engine(e), _window(e.window)
{
	_camera.Move(glm::vec3(0, -10, 20));
	_camera.Rotate(glm::vec3(0, 0, 1), 90);
	_camera.Rotate(glm::vec3(0, 1, 0), 64);

	build_level(_registry, _engine, level);
	_modelCache.load<systems::ModelLoader>(entt::HashedString("bomb"), ASSET_PATH "bomb.model");
	glClearColor(0.2, 0.25, 0.29, 1.0);

	if (level == "01" || level == "01")
	{
		auto waterSheet = _registry.create();
		_registry.assign<c::Position>(waterSheet, glm::vec3(0, 0, 0));
		_registry.assign<c::TimedEffect>(waterSheet, 100000.0f, scripts::destroy());
		_registry.assign<c::Particles>(waterSheet, Effects::water, 100000.0f);
	}
}

GameState::~GameState(void)
{
}

void GameState::Update(double dt)
{
	if (_window.Key(GLFW_KEY_ESCAPE))
		_engine.PushState(new PauseState(_engine));
	
	_cells(_registry);
	
	systems::RenderModels(_registry, _modelCache, _window, _camera, dt);
	systems::TimedEffect(_registry, dt);
	systems::Buttons(_registry, _window);
	systems::Images(_registry, _imageCache, _window);
	systems::Player(_registry, _window, _engine.keyBind, _cells, _camera, dt);
	systems::Velocity(_registry, _cells, dt);
	systems::RenderParticles(_registry, _camera);
	systems::Explosion(_registry, _cells);
	systems::AI(_registry, _window, dt);
	systems::Lighting(_registry, dt);
	systems::Danger(_registry, _cells);
}
