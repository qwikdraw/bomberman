#pragma once

#include <vector>
#include <string>
#include "Time.hpp"
#include "Window.hpp"
#include <entityx/entityx.h>

class IState;

//! Manages game States
class Engine
{
	std::vector<IState*> _states;
	Time _time;
public:
	Window& window;
	bool isRunning;
	Engine(Window& window);
	~Engine(void);
	void PushState(IState* state);
	void PopState(void);
	void ChangeState(IState* state);
	void Run(void);
	void Stop(void);
};
