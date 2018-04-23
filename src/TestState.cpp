#include "TestState.hpp"
#include "generate_level.hpp"
#include "ParticleExplosion.hpp"

TestState::TestState(Engine& e) :
_engine(e), _window(e.window)
{
	_camera.Move(glm::vec3(0, -10, 20));
	_camera.Rotate(glm::vec3(0, 0, 1), 90);
	_camera.Rotate(glm::vec3(0, 1, 0), 64);
	
	generate_level(_registry, 16, 16);

//generating test ai

	auto ai = _registry.create();
	_registry.assign<c::Model>(ai, "player", glm::mat4(1));
	_registry.assign<c::Velocity>(ai);
	_registry.assign<c::Collide>(ai);
	_registry.assign<c::AI>(ai, 2.0, 0.5);
	_registry.assign<c::Position>(ai, glm::vec3(0, 0, 0));
	
	_explosion = new ParticleExplosion(2.0f);
	glClearColor(0.2, 0.25, 0.29, 1.0);
}

TestState::~TestState(void)
{
}

void TestState::Update(double dt)
{
	_cells(_registry);
	systems::RenderModels(_registry, _modelCache, _window, _camera);
	systems::TimedEffect(_registry, dt);
	systems::Buttons(_registry, _imageCache, _window, dt);
	systems::Player(_registry, _window, _engine.keyBind, _camera, dt);
	systems::Velocity(_registry, _cells, dt);
	systems::RenderParticles(_registry, _camera);
	systems::Explosion(_registry, _cells, _explosion);
	systems::AI(_registry, _window, dt);
	systems::Lighting(_registry, dt);

}
