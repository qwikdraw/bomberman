#include "TestState.hpp"

void	thing(void)
{
	std::cout << "this worked" << std::endl;
}

void	TestStateEntityLoader(entt::DefaultRegistry &r)
{
	for (int x = -2; x < 13; x++)
	{
		for (int y = -2; y < 13; y++)
		{
			auto entity = r.create();
			if (abs(x % 2) + abs(y % 2) == 2 || x == -2 || x == 12 || y == -2 || y == 12)
			{
				r.assign<c::Model>(entity, "block", glm::mat4(1));
				r.assign<c::Collide>(entity);
			}
			else
				r.assign<c::Model>(entity, "floor", glm::mat4(1));
			r.assign<c::Position>(entity, glm::vec3(x, y, 0));
//			r.assign<c::Lighting>(entity, new Light(glm::vec3(x, y, 10), glm::vec3(0.1, 0.1, 0.1), 0.5));
		}
	}

	auto player = r.create();
	r.assign<c::Player>(player, 2.0, 1.0);
	r.assign<c::Model>(player, "block", glm::mat4(1));
	r.assign<c::Position>(player, glm::vec3(6, 0, 0));
	r.assign<c::Velocity>(player);
	r.assign<c::Particles>(player, new TestParticle());
}

TestState::TestState(Engine& e) :
_engine(e), _window(e.window)
{
	_camera.Move(glm::vec3(5, -10, 20));
	_camera.Rotate(glm::vec3(0, 0, 1), 90);
	_camera.Rotate(glm::vec3(0, 1, 0), 64);
	
	_lights.push_back(new Light(glm::vec3(5, 5, 2), glm::vec3(1, 1, 1), 30));
//	_lights.push_back(new Light(glm::vec3(5
	
	TestStateEntityLoader(_registry);
       
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
	systems::Player(_registry, _window, _cells, _camera, dt);
	systems::Velocity(_registry);
	systems::RenderParticles(_registry, _camera, dt);
}
