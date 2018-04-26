#pragma once

#include "bomberman.hpp"
#include "components.hpp"
#include "Effects.hpp"
#include "powerups.hpp"

namespace callbacks
{
	typedef std::function<void(entt::DefaultRegistry&, uint32_t)> callbackType;
	
	callbackType	explode(int power);

	callbackType	crateOnDeath(void);

	callbackType	destroy(void);
};
