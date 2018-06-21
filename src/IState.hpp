#pragma once

#include "Engine.hpp"

//! All screens must implement this interface
/*!
 * Screens include: menu, settings, level select, pause, game, death
*/

class IState
{
protected:
	IState() {}
public:
	virtual ~IState(void) {};

	//! All states must implement an Update method
	virtual void Update(double dt) = 0;
};

enum class StateType
{
	Menu,
	Level1,
	DeathScreen
};
