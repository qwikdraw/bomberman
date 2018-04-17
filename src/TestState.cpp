#include "TestState.hpp"
#include "components.hpp"
#include "bomberman.hpp"
#include "Systems.hpp"

void	thing(void)
{
	std::cout << "this worked" << std::endl;
}

TestState::TestState(Engine& e) :
_engine(e), _window(e.window)
{
	_camera.Move(glm::vec3(-5, 0, 0));
	_lights.push_back(new Light(glm::vec3(0, 0, 3), glm::vec3(1, 1, 1), 10));

	
	auto entity = _registry.create();
	_registry.assign<Part::Model>(entity, "MapBlock", glm::mat4(1));
	_registry.assign<Part::Position>(entity, glm::vec3(0, 0, 0));
	_registry.assign<Part::Decay>(entity, 50.0f);
	_registry.assign<Part::Button>(entity, "assets/png_files/TheMan.png", "assets/png_files/AlphaTest2.png",
				       thing, glm::vec2(0.7, 0.7), glm::vec2(0.8, 0.8), 0.1f);
	
	glClearColor(0.2, 0.25, 0.29, 1.0);
}

TestState::~TestState(void)
{
	for (auto l: _lights)
		delete l;
}

void TestState::Update(double dt)
{
	Systems::RenderModels(_registry, _modelCache, _window, _camera);
	Systems::Decay(_registry, dt);
	Systems::Buttons(_registry, _imageCache, _window, dt);
}
