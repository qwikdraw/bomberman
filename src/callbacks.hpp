#pragma once

#include "bomberman.hpp"
#include "components.hpp"
#include "Effects.hpp"
#include "powerups.hpp"

namespace callbacks
{
	typedef std::function<void(entt::DefaultRegistry&, uint32_t)> callbackType;
	
	callbackType	explode(int x, int y);

	callbackType	crateOnDeath(int x, int y);

	callbackType	destroy(void);
};
