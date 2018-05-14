#include <entt/entt.hpp>
#include "callbacks.hpp"

namespace c = components;

namespace callbacks
{

callback	explode(int power)
{
	return [power](entt::DefaultRegistry& r, uint32_t e)
	{
		auto ex = r.create();
		glm::vec3 &pos = r.get<c::Position>(e).pos;
		
		r.assign<c::Explosion>(ex, power);
		r.assign<c::Position>(ex, pos);
	};
}

callback	bomb(int power)
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

callback	powerup(float spawnChance)
{
	return [spawnChance](entt::DefaultRegistry& r, uint32_t e)
	{
		glm::vec3& pos = r.get<c::Position>(e).pos;

		if (glm::linearRand(0.0f, 1.0f) <= spawnChance)
			powerups::randomPowerup(r, pos);
	};
}

callback	destroy(void)
{
	return [](entt::DefaultRegistry& r, uint32_t e)
	{
		r.destroy(e);
	};
}

callback	change_state(entt::DefaultRegistry& r, StateType st)
{
	auto& engine = r.get<c::EngineTag>().ref;
	switch (st)
	{
	case StateType::Menu:
		return [&engine](entt::DefaultRegistry& r, uint32_t e)
		{
			engine.ChangeState(new TestState(engine));
		};
	case StateType::Level1:
		return [&engine](entt::DefaultRegistry& r, uint32_t e)
		{
			engine.ChangeState(new TestState(engine));
		};
	case StateType::DeathScreen:
		return [&engine](entt::DefaultRegistry& r, uint32_t e)
		{
			engine.ChangeState(new DeathState(engine));
		};
	}
}
}

callbacks::callback	operator + (callbacks::callback a, callbacks::callback b)
{
	auto f = [a, b](entt::DefaultRegistry& r, uint32_t e)
	{
		a(r, e);
		b(r, e);
	};
	return f;
}
