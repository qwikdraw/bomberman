#include <vector>
#include "Engine.hpp"
#include "IState.hpp"

Engine::Engine(Window& window) : _window(window), _isRunning(true) {}

Engine::~Engine(void) {}

void Engine::PushState(IState* state) {
	_states.push_back(state);
}

void Engine::PopState(void) {
	delete _states.back();
	_states.pop_back();
}

void Engine::ChangeState(IState* state) {
	delete _states.back();
	_states.pop_back();
	_states.push_back(state);
}

void Engine::Run(void) {
	_time.Step();
	_states.back()->Update(this, _window, _time.Delta());
	_states.back()->Draw(this, _window, _time.Delta());
}

void Engine::Stop(void) {
	for (auto s: _states) {
		delete s;
	}
	_states.clear();
	_isRunning = false;
}
