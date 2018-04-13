#include <vector>
#include "Engine.hpp"
#include "IState.hpp"

Engine::Engine(Window& window) : _window(window), isRunning(true) {}

Engine::~Engine(void) {
	for (auto s: _states) {
		delete s;
	}
	_states.clear();
	_window.Close();
}

void Engine::PushState(IState* state)
{
	_states.push_back(state);
}

void Engine::PopState(void)
{
	delete _states.back();
	_states.pop_back();
}

void Engine::ChangeState(IState* state)
{
	delete _states.back();
	_states.pop_back();
	_states.push_back(state);
}

void Engine::Run(void)
{
	_time.Step();
	_window.Clear();
	_states.back()->Update(this, _window, _time.Delta());
	_window.Render();
	if (_window.ShouldClose())
		isRunning = false;
	GLenum err;
	if ((err = glGetError()) != GL_NO_ERROR)
		std::cerr << err << std::endl;
}
