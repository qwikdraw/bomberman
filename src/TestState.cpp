#include "TestState.hpp"
#include "components.hpp"
#include "bomberman.hpp"

void a_system(entt::DefaultRegistry& registry, double dt, Model* bomb)
{
	auto view = registry.view<Position, Renderable>();
	for (auto entity : view)
	{
		auto &pos = view.get<Position>(entity);
		pos.x += dt;
		bomb->MoveTo(glm::vec3(pos.x, pos.y, pos.z));
		bomb->Render();
	}
}


TestState::TestState(Engine& e) :
_engine(e), _window(e.window), _camera(Camera())
{
	_camera.Move(glm::vec3(-5, 0, 0));
	_lights.push_back(new Light(glm::vec3(0, 0, 3), glm::vec3(1, 1, 1), 10));
	(void)_engine;
	_bomb = new Model("assets/MapBlock.model");
	
	auto ent = _registry.create(Position{0, (float)0, (float)0});
	_registry.assign<Renderable>(ent, "MapBlock");
	
	glClearColor(0.2, 0.25, 0.29, 1.0);
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
