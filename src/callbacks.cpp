#include "callbacks.hpp"

namespace c = components;

callbacks::callbackType	callbacks::explode(int x, int y)
{
	auto f = [x, y](entt::DefaultRegistry& r, uint32_t e)
	{
		auto ex = r.create();
		r.assign<c::Explosion>(ex, 4);
		r.assign<c::Position>(ex, glm::vec3(x, y, 0));
		r.destroy(e);
	};
	return f;
}

callbacks::callbackType	callbacks::crateOnDeath(int x, int y)
{
	auto f = [x, y](entt::DefaultRegistry& r, uint32_t e)
	{
		auto fire = r.create();

		r.assign<c::Position>(fire, glm::vec3(x, y, 0));
		r.assign<c::Lighting>(fire, glm::vec3(1, 1, 1), 2.0f, glm::vec3(0, 0, 2), -1.0f);
		r.assign<c::Dangerous>(fire, 100);
		r.assign<c::Particles>(fire, Effects::explosion, 2.0f);
		r.assign<c::TimedEffect>(fire, 2.0f, destroy());

		if (glm::linearRand(0.0f, 1.0f) < 0.5f)
			powerups::randomPowerup(r, x, y);
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
