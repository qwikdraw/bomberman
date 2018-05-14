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
	typedef std::function<void(entt::DefaultRegistry&, uint32_t)> script;

	script explode(int power);
	script bomb(int power);
	script powerup(float spawnChance);
	script destroy(void);
	script change_state(entt::DefaultRegistry& r, StateType st);
};

scripts::script	operator+ (scripts::script, scripts::script);
