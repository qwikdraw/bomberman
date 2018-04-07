#pragma once

#include "Engine.hpp"

//! Game states must implement this abstract class
class IState
{
protected:
	IState() {}
public:
	virtual ~IState(void) {};
	virtual void Update(Engine* game, Window& window, double dt) = 0;
	virtual void Draw(Engine* game, Window& window, double dt) = 0;
};
