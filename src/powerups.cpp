#include "powerups.hpp"

namespace c = components;

void	powerups::randomPowerup(entt::DefaultRegistry& r, glm::vec3 pos)
{
	//might want to rework if we end up with a ton of powerups
	if (glm::linearRand(0.0f, 1.0f) <= 0.5)
		speedBoost(r, pos);
	else
		bombPower(r, pos);
}

void	powerups::speedBoost(entt::DefaultRegistry& r, glm::vec3 pos)
{
	auto powerup = r.create();

	auto effect = [powerup](entt::DefaultRegistry& reg, uint32_t e)
	{
		auto &player = reg.get<c::Player>();

		player.speed += 0.5;
		reg.destroy(powerup);
	};
	
	r.assign<c::Position>(powerup, pos);
	r.assign<c::Model>(powerup, "speed_boost", glm::mat4(1));
	r.assign<c::Powerup>(powerup, effect);
}

void	powerups::bombPower(entt::DefaultRegistry& r, glm::vec3 pos)
{
	auto powerup = r.create();

	auto effect = [powerup](entt::DefaultRegistry& reg, uint32_t e)
	{
		auto &player = reg.get<c::Player>();

		player.bombPower++;
		reg.destroy(powerup);
	};

	r.assign<c::Position>(powerup, pos);
	r.assign<c::Model>(powerup, "more_power", glm::mat4(1));
	r.assign<c::Powerup>(powerup, effect);
}
