#pragma once

#include <vector>
#include <string>
#include "Time.hpp"
#include "Window.hpp"

class IState;

//! Manages game States
class Engine
{
	std::vector<IState*> _states;
	Time _time;
	Window _window;
	bool _isRunning;
public:
	Engine(Window& window);
	~Engine(void);
	void PushState(IState* state);
	void PopState(void);
	void ChangeState(IState* state);
	void Run(void);
	void Stop(void);
};
