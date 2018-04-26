#include "TestState.hpp"
#include "generate_level.hpp"
#include "ParticleExplosion.hpp"

TestState::TestState(Engine& e) :
_engine(e), _window(e.window)
{
	_camera.Move(glm::vec3(0, -10, 20));
	_camera.Rotate(glm::vec3(0, 0, 1), 90);
	_camera.Rotate(glm::vec3(0, 1, 0), 64);

	Effects::explosion = new ParticleExplosion(2.0f);
	
	generate_level(_registry, 16, 16);

	glClearColor(0.2, 0.25, 0.29, 1.0);
}

TestState::~TestState(void)
{
	Effects::CleanUp();
}

void TestState::Update(double dt)
{
	_cellQuery.Update(_registry);
	
	systems::RenderModels(_registry, _modelCache, _window, _camera);
	systems::TimedEffect(_registry, dt);
	systems::Buttons(_registry, _imageCache, _window, dt);
	systems::Player(_registry, _window, _engine.keyBind, _cellQuery, _camera, dt);
	systems::Velocity(_registry, _cellQuery, dt);
	systems::RenderParticles(_registry, _camera);
	systems::Explosion(_registry, _cellQuery);
	systems::AI(_registry, _window, dt);
	systems::Lighting(_registry, dt);
	systems::DangerCheck(_registry, _cellQuery);
}
