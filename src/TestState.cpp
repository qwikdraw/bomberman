#include "TestState.hpp"
#include "ObjFile.hpp"
#include "components.hpp"
#include "bomberman.hpp"

void a_system(entt::DefaultRegistry& registry, double dt, ObjFile* bomb)
{
	auto view = registry.view<Position, Renderable>();
	for (auto entity : view)
	{
		auto &pos = view.get<Position>(entity);
		pos.x += dt;
		bomb->Render(glm::vec3(pos.x, pos.y, pos.z));
	}
}


TestState::TestState(Engine& e) :
_engine(e), _window(e.window), _camera(Camera())
{
	_camera.Move(glm::vec3(-5, 0, 0));
	_lights.push_back(new Light(glm::vec3(0, 0, 3), glm::vec3(1, 1, 1), 10));
	(void)_engine;
	_bomb = new ObjFile("assets/bomb.obj", "assets/tulips.bmp");
	for (int y = -5; y < 5; ++y)
	{
		for (int z = -5; z < 5; ++z)
		{
			auto ent = _registry.create(Position{0, (float)y, (float)z});
			_registry.assign<Renderable>(ent, "bomb");
		}
	}
	glClearColor(0.3, 0.3, 0.3, 1.0);
}

TestState::~TestState(void)
{
	for (auto l: _lights)
		delete l;
}

void TestState::Update(double dt)
{
	_camera.SetAspect(_window.GetAspect());
	_bomb->UsePerspective(_camera.Perspective());
	a_system(_registry, dt, _bomb);
}
