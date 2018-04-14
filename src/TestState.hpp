#pragma once

#include "bomberman.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "IState.hpp"

class TestState : public IState, public ex::EntityX
{
	Engine& _engine;
	Window& _window;
	Camera _camera;
	std::vector<Light*> _lights;
public:
	TestState(Engine& engine);
	~TestState(void);
	void Update(double dt);
};
