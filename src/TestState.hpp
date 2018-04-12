#pragma once

#include "AnimatedObject.hpp"
#include "Camera.hpp"
#include "Light.hpp"

#include "IState.hpp"

class TestState : public IState
{
	Camera _camera;
	AnimatedObject _animation;
	std::vector<Light*> _lights;
public:
	TestState(void);
	~TestState(void);
	void Update(Engine*, Window& window, double);
	void Draw(Engine*, Window& window, double);
};
