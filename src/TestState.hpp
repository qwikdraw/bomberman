#pragma once

#include "bomberman.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "IState.hpp"
#include "ObjFile.hpp"
#include <entt/entt.hpp>

class TestState : public IState
{
	Engine& _engine;
	Window& _window;
	Camera _camera;
	std::vector<Light*> _lights;
	entt::DefaultRegistry _registry;
	ObjFile* _bomb;
public:
	TestState(Engine& engine);
	~TestState(void);
	void Update(double dt);
};
