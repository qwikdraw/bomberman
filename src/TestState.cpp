#include "TestState.hpp"
#include "components.hpp"

class MovementSystem : public ex::System<MovementSystem> {
public:
	explicit MovementSystem(void) {}
	void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override {
		std::cout << "things" << std::endl;
		es.each<CellPosition>([](ex::Entity, CellPosition& pos) {
			pos.x += 1;
			std::cout << "Position x = " << pos.x << std::endl;
		});
	}
};

TestState::TestState(Engine& e) :
_engine(e), _window(e.window), _camera(Camera())
{
	_camera.Move(glm::vec3(-10, 0, 3));
	for (int i = 0; i < 10; ++i)
		_lights.push_back(new Light(glm::vec3(0, 0, 4), glm::vec3(1, 1, 1), 2));
	systems.add<MovementSystem>();
	systems.configure();
	(void)_engine;
	ex::Entity ent = entities.create();
	ent.assign<CellPosition>(0,0);
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
