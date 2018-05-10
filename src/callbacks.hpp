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
	typedef std::function<void(entt::DefaultRegistry&, uint32_t)> callbackType;

	callbackType	explode(int power);
	callbackType	ignite(void);
	callbackType	bomb(int power);
	callbackType	powerup(float spawnChance);
	callbackType	destroy(void);

	callbackType	change_state(StateType st, Engine& engine);
};

callbacks::callbackType	operator + (callbacks::callbackType, callbacks::callbackType);
