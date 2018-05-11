#include <vector>
#include "Engine.hpp"
#include "IState.hpp"

Engine::Engine(Window& w) : window(w), isRunning(true)
{
	keyBind.up = 'W';
	keyBind.down = 'S';
	keyBind.right = 'D';
	keyBind.left = 'A';
	keyBind.bomb = ' ';
}

Engine::~Engine(void) {
	for (auto s: _states) {
		delete s;
	}
	_states.clear();
	window.Close();
}

void Engine::PushState(IState* state)
{
	_states.push_back(state);
}

void Engine::PopState(void)
{
	_deleteMe = _states.back();
	_states.pop_back();
}

void Engine::ChangeState(IState* state)
{
	_deleteMe = _states.back();
	_states.pop_back();
	_states.push_back(state);
}

void Engine::Run(void)
{
	_time.Step();
	window.Clear();
	
	_states.back()->Update(std::min(_time.Delta(), 0.2));

	if (_deleteMe)
	{
		delete _deleteMe;
		_deleteMe = nullptr;
	}
	
	window.Render();
	if (window.ShouldClose())
		isRunning = false;
	GLenum err;
	if ((err = glGetError()) != GL_NO_ERROR)
		std::cerr << err << std::endl;
}
