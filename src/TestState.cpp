#include "TestState.hpp"
#include "components.hpp"
#include "bomberman.hpp"
#include "systems.hpp"

namespace c = components;

void	thing(void)
{
	std::cout << "this worked" << std::endl;
}

void	TestStateEntityLoader(entt::DefaultRegistry &r)
{
	/*
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			auto entity = r.create();
			if ((x % 2) + (y % 2) == 1)
				r.assign<Part::Model>(entity, "MapBlock", glm::mat4(1));
			else
				r.assign<Part::Model>(entity, "MapFloor", glm::mat4(1));
			r.assign<Part::Position>(entity, glm::vec3(x, y, 0));
		}
	}
	*/

	auto entity = r.create();
	r.assign<c::Model>(entity, "block", glm::mat4(1));
	r.assign<c::Position>(entity, glm::vec3(0, 0, 0));
}

TestState::TestState(Engine& e) :
_engine(e), _window(e.window)
{
//	_camera.Rotate(glm::vec3(0, 0, 1), 90);
//	_camera.Move(glm::vec3(0, 0, 20));
//	_camera.Rotate(glm::vec3(0, 0, 0), 90);

	_camera.Move(glm::vec3(-3.5, 0, 0));
	_camera.Rotate(glm::vec3(0, 1, 0), 10);
	
	_lights.push_back(new Light(glm::vec3(0, 0, 3), glm::vec3(1, 1, 1), 10));

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
	systems::RenderModels(_registry, _modelCache, _window, _camera);
	systems::Decay(_registry, dt);
	systems::Buttons(_registry, _imageCache, _window, dt);
}
