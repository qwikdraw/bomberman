#pragma once

#include "IState.hpp"

class TestState : public IState
{
public:
	TestState(void);
	~TestState(void);
	void Update(Engine*, Window& window, double);
	void Draw(Engine*, Window& window, double);
};
