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
		r.destroy(e);
	};
	return f;
}

callbacks::callbackType	callbacks::crateOnDeath(void)
{
	auto f = [](entt::DefaultRegistry& r, uint32_t e)
	{
		auto fire = r.create();
		glm::vec3 &pos = r.get<c::Position>(e).pos;
		
		r.assign<c::Position>(fire, pos);
		r.assign<c::Lighting>(fire, glm::vec3(1, 1, 1), 2.0f, glm::vec3(0, 0, 2), -1.0f);
		r.assign<c::Dangerous>(fire, 100);
		r.assign<c::Particles>(fire, Effects::explosion, 2.0f);
		r.assign<c::TimedEffect>(fire, 2.0f, destroy());

		if (glm::linearRand(0.0f, 1.0f) < 0.5f)
			powerups::randomPowerup(r, pos);
		r.destroy(e);
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
