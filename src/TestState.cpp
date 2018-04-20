#include "TestState.hpp"
#include "generate_level.hpp"

void	thing(void)
{
	std::cout << "this worked" << std::endl;
}

TestState::TestState(Engine& e) :
_engine(e), _window(e.window)
{
	_camera.Move(glm::vec3(0, -10, 20));
	_camera.Rotate(glm::vec3(0, 0, 1), 90);
	_camera.Rotate(glm::vec3(0, 1, 0), 64);
	
	_lights.push_back(new Light(glm::vec3(5, 5, 10), glm::vec3(1, 1, 1), 30));
//	_lights.push_back(new Light(glm::vec3(5
	generate_level(_registry, 10, 10);
	glClearColor(0.2, 0.25, 0.29, 1.0);
}

TestState::~TestState(void)
{
	for (auto l: _lights)
		delete l;
}

void TestState::Update(double dt)
{
	_cells(_registry);
	systems::RenderModels(_registry, _modelCache, _window, _camera);
	systems::Decay(_registry, dt);
	systems::Buttons(_registry, _imageCache, _window, dt);
	systems::Player(_registry, _window, _engine.keyBind, _camera, dt);
	systems::Velocity(_registry, _cells, dt);
	systems::RenderParticles(_registry, _camera, dt);
}
