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
public:
	Engine(std::string name);
	~Engine(void);
	void PushState(IState* state);
	void PopState(void);
	void Update(void);
	void Draw(void);
};
