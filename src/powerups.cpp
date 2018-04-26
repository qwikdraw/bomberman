#include "powerups.hpp"

namespace c = components;

void	powerups::randomPowerup(entt::DefaultRegistry& r, glm::vec3 pos)
{
	speedBoost(r, pos);
}

void	powerups::speedBoost(entt::DefaultRegistry& r, glm::vec3 pos)
{
	auto powerup = r.create();

	auto effect = [powerup](entt::DefaultRegistry& reg, uint32_t e)
	{
		auto &player = reg.get<c::Player>(e);

		player.speed += 0.5;
		reg.destroy(powerup);
	};
	
	r.assign<c::Position>(powerup, pos);
	r.assign<c::Model>(powerup, "speed_boost", glm::mat4(1));
	r.assign<c::Powerup>(powerup, effect);
}
