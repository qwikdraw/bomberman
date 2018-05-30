#pragma once

#include "bomberman.hpp"
#include "components.hpp"
#include "Effects.hpp"
#include "powerups.hpp"
#include "Engine.hpp"

#include "GameState.hpp"
#include "DeathState.hpp"

namespace scripts
{
	script explode(int power, ISoundEngine& sound);
	script bomb(int power, ISoundEngine& sound);
	script powerup(float spawnChance);
	script destroy(void);
	script switch_level(std::string level);
	script death(std::string level);
};

scripts::script	operator+ (scripts::script, scripts::script);
