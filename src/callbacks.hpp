#pragma once

#include "bomberman.hpp"
#include "components.hpp"
#include "Effects.hpp"
#include "powerups.hpp"
#include "Engine.hpp"

#include "TestState.hpp"
#include "DeathState.hpp"

namespace callbacks
{
	typedef std::function<void(entt::DefaultRegistry&, uint32_t)> callback;

	callback explode(int power);
	callback ignite(void);
	callback bomb(int power);
	callback powerup(float spawnChance);
	callback destroy(void);
	callback change_state(entt::DefaultRegistry& r, StateType st);
};

callbacks::callback	operator+ (callbacks::callback, callbacks::callback);
