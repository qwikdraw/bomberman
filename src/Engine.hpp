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
public:

	struct KeyBind
	{
		int up;
		int down;
		int left;
		int right;
		int bomb;
	};	
	
	Window& window;
	bool isRunning;
	KeyBind keyBind;
	Engine(Window& window);
	~Engine(void);
	void PushState(IState* state);
	void PopState(void);
	void ChangeState(IState* state);
	void Run(void);
};
