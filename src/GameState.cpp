#include "GameState.hpp"
#include "ParticleExplosion.hpp"
#include "build_level.hpp"

GameState::GameState(Engine& e) :
_engine(e), _window(e.window)
{
	_camera.Move(glm::vec3(0, -10, 20));
	_camera.Rotate(glm::vec3(0, 0, 1), 90);
	_camera.Rotate(glm::vec3(0, 1, 0), 64);

	build_level(_registry, "01", _engine);
	_modelCache.load<systems::ModelLoader>(entt::HashedString("bomb"), ASSET_PATH "bomb.model");
	glClearColor(0.2, 0.25, 0.29, 1.0);
}

GameState::~GameState(void)
{
}

void GameState::Update(double dt)
{
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
