#include "callbacks.hpp"

namespace c = components;

callbacks::callbackType	callbacks::explode(int power)
{
	auto f = [power](entt::DefaultRegistry& r, uint32_t e)
	{
		auto ex = r.create();
		glm::vec3 &pos = r.get<c::Position>(e).pos;
		
		r.assign<c::Explosion>(ex, power);
		r.assign<c::Position>(ex, pos);
	};
	return f;
}

callbacks::callbackType	callbacks::ignite(void)
{
	auto f = [](entt::DefaultRegistry& r, uint32_t e)
	{
		auto fire = r.create();
		glm::vec3& pos = r.get<c::Position>(e).pos;

		r.assign<c::Position>(fire, pos);
		r.assign<c::Lighting>(fire, glm::vec3(1, 0.5, 0.5), 2.0f, glm::vec3(0, 0, 2), -1.0f);
		r.assign<c::Dangerous>(fire, 100);
		r.assign<c::TimedEffect>(fire, 2.0f, destroy());
		r.assign<c::Particles>(fire, Effects::explosion, 2.0f);
	};
	return f;
}

callbacks::callbackType	callbacks::bomb(int power)
{
	auto f = [power](entt::DefaultRegistry& r, uint32_t e)
	{
		auto bomb = r.create();
		glm::vec3& pos = r.get<c::Position>(e).pos;

		r.assign<c::Position>(bomb, glm::round(pos));
		r.assign<c::Model>(bomb, "bomb", glm::mat4(1));
		r.assign<c::Collide>(bomb);
		r.assign<c::TimedEffect>(bomb, 3.0f, explode(power) + destroy());
		r.assign<c::Vulnerable>(bomb, explode(power) + destroy(), 50);
	};
	return f;
}

callbacks::callbackType	callbacks::powerup(float spawnChance)
{
	auto f = [spawnChance](entt::DefaultRegistry& r, uint32_t e)
	{
		glm::vec3& pos = r.get<c::Position>(e).pos;

		if (glm::linearRand(0.0f, 1.0f) <= spawnChance)
			powerups::randomPowerup(r, pos);
	};
	return f;
}

callbacks::callbackType	callbacks::destroy(void)
{
	auto f = [](entt::DefaultRegistry& r, uint32_t e)
	{
		r.destroy(e);
	};
	return f;
}

callbacks::callbackType	operator + (callbacks::callbackType a, callbacks::callbackType b)
{
	auto f = [a, b](entt::DefaultRegistry& r, uint32_t e)
	{
		a(r, e);
		b(r, e);
	};
	return f;
}
