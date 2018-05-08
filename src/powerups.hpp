#pragma once

#include "bomberman.hpp"
#include "components.hpp"

namespace powerups
{
	void	randomPowerup(entt::DefaultRegistry&, glm::vec3 pos);

	void	speedBoost(entt::DefaultRegistry&, glm::vec3 pos);

	void	bombPower(entt::DefaultRegistry&, glm::vec3 pos);
};
