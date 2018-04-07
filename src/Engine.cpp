#include <vector>
#include "Engine.hpp"
#include "IState.hpp"

Engine::Engine(std::string name) : _window(Window(1024, 1024, name)) {}

Engine::~Engine(void) {}

void Engine::PushState(IState* state) {
	_states.push_back(state);
}

void Engine::PopState(void) {
	delete _states.back();
	_states.pop_back();
}

void Engine::Update(void) {
	_time.Step();
	_states.back()->Update(this, _window, _time.Delta());
}

void Engine::Draw(void) {
	_states.back()->Draw(this, _window, _time.Delta());
}
