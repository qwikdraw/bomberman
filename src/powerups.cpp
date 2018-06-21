#include "powerups.hpp"

namespace c = components;

namespace powerups
{

void	randomPowerup(entt::DefaultRegistry& r, glm::vec3 pos)
{
	//might want to rework if we end up with a ton of powerups
	if (glm::linearRand(0.0f, 1.0f) <= 0.5)
		speedBoost(r, pos);
	else
		bombPower(r, pos);
}

void	speedBoost(entt::DefaultRegistry& r, glm::vec3 pos)
{
	auto powerup = r.create();

	auto effect = [powerup](entt::DefaultRegistry& reg, uint32_t)
	{
		auto &player = reg.get<c::Player>();
		auto &engine = reg.get<c::EngineTag>().ref;

		engine.sound.play2D(ASSET_PATH "sounds/powerup.wav");
		player.speed += 0.5;
		reg.destroy(powerup);
	};

	r.assign<c::Position>(powerup, pos);
	r.assign<c::Model>(powerup, "models/common/speed_boost", glm::mat4(1));
	r.assign<c::Powerup>(powerup, effect);
}

void	bombPower(entt::DefaultRegistry& r, glm::vec3 pos)
{
	auto powerup = r.create();

	auto effect = [powerup](entt::DefaultRegistry& reg, uint32_t)
	{
		auto &player = reg.get<c::Player>();
		auto &engine = reg.get<c::EngineTag>().ref;

		engine.sound.play2D(ASSET_PATH "sounds/powerup.wav");
		player.bombPower++;
		reg.destroy(powerup);
	};

	r.assign<c::Position>(powerup, pos);
	r.assign<c::Model>(powerup, "more_power", glm::mat4(1));
	r.assign<c::Powerup>(powerup, effect);
}

}
