#pragma once

#include "bomberman.hpp"
#include "components.hpp"

//! power up types
namespace powerups
{
	//! spawns a random powerup
	void	randomPowerup(entt::DefaultRegistry&, glm::vec3 pos);

	//! spawns a speed powerup
	void	speedBoost(entt::DefaultRegistry&, glm::vec3 pos);

	//! spawns a bomb power powerup
	void	bombPower(entt::DefaultRegistry&, glm::vec3 pos);
};
