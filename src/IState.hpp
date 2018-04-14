#pragma once

#include "Engine.hpp"
#include <entityx/entityx.h>
namespace ex = entityx;


//! Game states must implement this abstract class
class IState
{
protected:
	IState() {}
public:
	virtual ~IState(void) {};
	virtual void Update(double dt) = 0;
};
