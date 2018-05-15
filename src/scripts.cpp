#include "scripts.hpp"
namespace c = components;

namespace scripts
{

script	explode(int power)
{
	return [power](entt::DefaultRegistry& r, uint32_t e)
	{
		auto ex = r.create();
		glm::vec3 &pos = r.get<c::Position>(e).pos;
		
		r.assign<c::Explosion>(ex, power);
		r.assign<c::Position>(ex, pos);
	};
}

script	bomb(int power)
{
	return [power](entt::DefaultRegistry& r, uint32_t e)
	{
		auto bomb = r.create();
		glm::vec3& pos = r.get<c::Position>(e).pos;

		r.assign<c::Position>(bomb, glm::round(pos));
		r.assign<c::Model>(bomb, "bomb", glm::mat4(1));
		r.assign<c::Collide>(bomb);
		r.assign<c::Lighting>(bomb, glm::vec3(-10, -10, -10), 0.2f, glm::vec3(0, 0, 0.1));
		r.assign<c::TimedEffect>(bomb, 3.0f, explode(power) + destroy());
		r.assign<c::Vulnerable>(bomb, explode(power) + destroy(), 50);
	};
}

script	powerup(float spawnChance)
{
	return [spawnChance](entt::DefaultRegistry& r, uint32_t e)
	{
		glm::vec3& pos = r.get<c::Position>(e).pos;

		if (glm::linearRand(0.0f, 1.0f) <= spawnChance)
			powerups::randomPowerup(r, pos);
	};
}

script	destroy(void)
{
	return [](entt::DefaultRegistry& r, uint32_t e)
	{
		r.destroy(e);
	};
}

script	switch_level(std::string level)
{
	return [level](entt::DefaultRegistry& r, uint32_t e)
	{
		auto& engine = r.get<c::EngineTag>().ref;
		engine.ChangeState(new GameState(engine, level));
	};
}

script	death(std::string level)
{
	return [level](entt::DefaultRegistry& r, uint32_t e)
	{
		auto& engine = r.get<c::EngineTag>().ref;
		engine.ChangeState(new DeathState(engine, level));
	};
}
}

scripts::script	operator+(scripts::script a, scripts::script b)
{
	return [a, b](entt::DefaultRegistry& r, uint32_t e)
	{
		a(r, e);
		b(r, e);
	};
}
