#include "TestState.hpp"
#include "generate_level.hpp"

void	TestState::init_particles()
{
	std::vector<float> &pos = _particles.GetPhysicalAttributes();
	std::vector<float> &col = _particles.GetColorAttributes();

	_lifetime.resize(pos.size());
	_speed.resize(pos.size());

	for (size_t i = 0; i < pos.size(); i+= 4)
	{
		pos[i] = 0;
		pos[i + 1] = 0;
		pos[i + 2] = 0;
		pos[i + 3] = 0.01;
		_speed[i] = (0.5 - (rand() % 100 / 100.0)) * 0.01;
		_speed[i + 1] = (0.5 - (rand() % 100 / 100.0)) * 0.01;
		_speed[i + 2] = (0.5 - (rand() % 100 / 100.0)) * 0.01;
		col[i] = (rand() % 50) * 0.01 + .5;
		col[i + 1] = (rand() % 20) * 0.01 + .1;
		col[i + 2] = (rand() % 10) * 0.01;
		col[i + 3] = 0.5;
	}

	_particles.SetTransform(glm::translate(glm::vec3(0, 0, 5)));
}

void	TestState::update_particles()
{
	std::vector<float> &pos = _particles.GetPhysicalAttributes();
//	std::vector<size_t> &idx = _particles.GetAttributeIndices();
//	std::vector<float> &col = _particles.GetColorAttributes();

	for (size_t i = 0; i < pos.size(); i+=4)
	{
		_speed[i] += _speed[i] > 0 ? -0.01 : 0.01;
		_speed[i + 1] += _speed[i + 1] > 0 ? -0.01 : 0.01;
		_speed[i + 2] += _speed[i + 2] > 0 ? -0.01 : 0.01;
		pos[i] += _speed[i];
		pos[i + 1] += _speed[i + 1];
		pos[i + 2] += _speed[i + 2];
	}
}

TestState::TestState(Engine& e) :
_particles(Particles(10000)), _engine(e), _window(e.window)
{
	_camera.Move(glm::vec3(0, -10, 20));
	_camera.Rotate(glm::vec3(0, 0, 1), 90);
	_camera.Rotate(glm::vec3(0, 1, 0), 64);
	
	generate_level(_registry, 12, 12);
	glClearColor(0.2, 0.25, 0.29, 1.0);


	init_particles();
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
	systems::RenderParticles(_registry, _camera, dt);
	systems::Explosion(_registry, _cells);
}
