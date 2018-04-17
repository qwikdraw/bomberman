#include "TestState.hpp"
#include "components.hpp"
#include "bomberman.hpp"
#include "Systems.hpp"

TestState::TestState(Engine& e) :
_engine(e), _window(e.window), _camera(Camera())
{
	_camera.Move(glm::vec3(-5, 0, 0));
	_lights.push_back(new Light(glm::vec3(0, 0, 3), glm::vec3(1, 1, 1), 10));

	
	auto entity = _registry.create();
	_registry.assign<Part::Model>(entity, "MapBlock", glm::mat4(1));
	_registry.assign<Part::Position>(entity, glm::vec3(0, 0, 0));
	_registry.assign<Part::Decay>(entity, 5.0f);
	
	glClearColor(0.2, 0.25, 0.29, 1.0);
}

TestState::~TestState(void)
{
	for (auto l: _lights)
		delete l;
}

void TestState::Update(double dt)
{
	Systems::RenderModels(_registry, _camera);
	Systems::Decay(_registry, dt);
}
