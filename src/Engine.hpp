#pragma once

#include <vector>
#include <string>
#include "Time.hpp"
#include "Window.hpp"

class IState;

//! Game State Manager
class Engine
{	
	std::vector<IState*> _states;
	Time _time;
	IState *_deleteMe;
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
	i::ISoundEngine& sound;
	bool isRunning;
	KeyBind keyBind;
	//! Engine takes a window are sound device.
	Engine(Window& window, i::ISoundEngine& sound);
	~Engine(void);
	//! Add a state to the top of the state stack.
	void PushState(IState* state);
	//! Remove the top state from the state stack.
	void PopState(void);
	//! Remove the top state and push another (PopState + PushState).
	void ChangeState(IState* state);
	//! Run a tick of the game.
	void Run(void);
};
