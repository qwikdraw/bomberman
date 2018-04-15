#include "TestState.hpp"
#include "ObjFile.hpp"
#include "components.hpp"
#include "bomberman.hpp"

class MovementSystem : public ex::System<MovementSystem> {
public:
	MovementSystem(void) {}
	void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override {
		es.each<CellPosition>([](ex::Entity, CellPosition& pos) {
			pos.x += 0;
		});
	}
};

class RenderSystem : public ex::System<RenderSystem> {
	Camera& _cam;
public:
	RenderSystem(Camera& c) : _cam(c) {}
	void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override {
		es.each<Obj, CellPosition>([this](ex::Entity, Obj& r, CellPosition& p) {
			r.obj->UsePerspective(_cam.Perspective());
			r.obj->Render(glm::vec3(p.x, p.y, 0));
		});
	}
};

TestState::TestState(Engine& e) :
_engine(e), _window(e.window), _camera(Camera())
{
	_camera.Move(glm::vec3(-5, 0, 0));
	_lights.push_back(new Light(glm::vec3(0, 0, 3), glm::vec3(1, 1, 1), 10));
	systems.add<MovementSystem>();
	systems.add<RenderSystem>(_camera);
	systems.configure();
	(void)_engine;
	ex::Entity ent = entities.create();
	ent.assign<CellPosition>(0,0);
	ent.assign<Obj>(new ObjFile("assets/bomb.obj", "assets/tulips.bmp"));
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
	systems.update_all(dt);
}
