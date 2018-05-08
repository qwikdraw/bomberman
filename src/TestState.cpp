#include "TestState.hpp"
#include "generate_level.hpp"
#include "ParticleExplosion.hpp"

TestState::TestState(Engine& e) :
_engine(e), _window(e.window)
{
	_camera.Move(glm::vec3(0, -10, 20));
	_camera.Rotate(glm::vec3(0, 0, 1), 90);
	_camera.Rotate(glm::vec3(0, 1, 0), 64);

	Effects::explosion = new ParticleExplosion(1.0f);

// create AI test

	auto enemy = _registry.create();
	_registry.assign<c::Position>(enemy, glm::vec3(1, 3, 0));
	_registry.assign<c::Model>(enemy, "player", glm::mat4(1));
	_registry.assign<c::Velocity>(enemy);
	_registry.assign<c::Collide>(enemy, 1);
	_registry.assign<c::AI>(enemy, 2.0, 1.0, c::AI_type::HORZ);
	_registry.assign<c::Dangerous>(enemy, 10);
	_registry.assign<c::Vulnerable>(enemy, callbacks::explode(3) + callbacks::destroy(), 11);

	auto enemy_v = _registry.create();
	_registry.assign<c::Position>(enemy_v, glm::vec3(3, 1, 0));
	_registry.assign<c::Model>(enemy_v, "player", glm::mat4(1));
	_registry.assign<c::Velocity>(enemy_v);
	_registry.assign<c::Collide>(enemy_v, 1);
	_registry.assign<c::AI>(enemy_v, 2.0, 1.0, c::AI_type::VERT);
	_registry.assign<c::Dangerous>(enemy_v, 10);
	_registry.assign<c::Vulnerable>(enemy_v, callbacks::explode(3) + callbacks::destroy(), 11);

	auto enemy_r = _registry.create();
	_registry.assign<c::Position>(enemy_r, glm::vec3(-3, -3, 0));
	_registry.assign<c::Model>(enemy_r, "player", glm::mat4(1));
	_registry.assign<c::Velocity>(enemy_r);
	_registry.assign<c::Collide>(enemy_r, 1);
	_registry.assign<c::AI>(enemy_r, 2.0, 1.0, c::AI_type::RAND);
	_registry.assign<c::Dangerous>(enemy_r, 10);
	_registry.assign<c::Vulnerable>(enemy_r, callbacks::explode(3) + callbacks::destroy(), 11);


	generate_level(_registry, 16, 16, _engine);

	glClearColor(0.2, 0.25, 0.29, 1.0);
}

TestState::~TestState(void)
{
	Effects::CleanUp();
}

void TestState::Update(double dt)
{
	_cellQuery.Update(_registry);
	
	systems::RenderModels(_registry, _modelCache, _window, _camera, dt);
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
