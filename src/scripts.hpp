#pragma once

#include "bomberman.hpp"
#include "components.hpp"
#include "Effects.hpp"
#include "powerups.hpp"
#include "Engine.hpp"

#include "GameState.hpp"
#include "DeathState.hpp"
#include "CreditState.hpp"

//! a list of functions that return custom scripts
namespace scripts
{
	//! returns an explode script that causes an explosion with given power
	script explode(int power);
	//! returns a bomb script that spawns a bomb with given power
	script bomb(int power);
	//! returns a powerup script that spawns a random powerup based on spawnChance
	script powerup(float spawnChance);
	//! returns a script that will destroy an entity
	script destroy(void);
	//! returns a script that will switch the level to the one given as argument
	script switch_level(std::string level);
	//! returns a script that will trigger a death sequence from a particular level
	script death(std::string level);
};

//! allows script chaining
scripts::script	operator+ (scripts::script, scripts::script);
