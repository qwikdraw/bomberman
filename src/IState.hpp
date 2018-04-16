#pragma once

#include "Engine.hpp"

//! Game states must implement this interface
class IState
{
protected:
	IState() {}
public:
	virtual ~IState(void) {};
	virtual void Update(double dt) = 0;
};
