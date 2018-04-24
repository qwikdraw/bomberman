#include "generate_level.hpp"
#include <random>

static glm::mat4 random_direction()
{
	static const glm::mat4 dirs[4] = {
		glm::mat4(1),
		glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(0, 0, 1)),
		glm::rotate(glm::mat4(1), glm::radians(180.0f), glm::vec3(0, 0, 1)),
		glm::rotate(glm::mat4(1), glm::radians(270.0f), glm::vec3(0, 0, 1)),
	};
	static std::mt19937 rng;

	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> pick_dir(0, 3);
	return dirs[pick_dir(rng)];
}

static void spawn_player(entt::DefaultRegistry &r, int x, int y)
{
	auto player = r.create();
	
	auto deathSequence = [&r, player]()
	{
		r.destroy(player);
	};

	r.assign<c::Player>(player, 2.0, 1.0);
	r.assign<c::Model>(player, "player", glm::mat4(1));
	r.assign<c::Position>(player, glm::vec3(x, y, 0));
	r.assign<c::Velocity>(player);
	r.assign<c::Collide>(player, 1);
	r.assign<c::Vulnerable>(player, deathSequence);
}

static void spawn_wall(entt::DefaultRegistry &r, std::string type, int x, int y)
{
	auto wall = r.create();
	r.assign<c::Model>(wall, type, glm::mat4(1));
	r.assign<c::Collide>(wall, 100000);
	r.assign<c::Position>(wall, glm::vec3(x, y, 0));
}

static void spawn_crate(entt::DefaultRegistry &r, int x, int y, ParticleExplosion *expl)
{
	auto e = r.create();
	
	auto crateDestruction = [&r, e, expl, x, y]()
	{
		auto fire = r.create();

		r.assign<c::Position>(fire, glm::vec3(x, y, 0));
		r.assign<c::Lighting>(fire, glm::vec3(1, 1, 1), 2.0f, glm::vec3(0, 0, 2), -1.0f);
		r.assign<c::Dangerous>(fire, 100);
		r.assign<c::Particles>(fire, expl, 2.0f);
		r.assign<c::TimedEffect>(fire, 2.0f);

		//powerup spawn
		if (glm::linearRand(0.0f, 1.0f) < 0.5f)
		{
			r.destroy(e);
			return;
		}
		
		auto pow = r.create();

		auto effect = [&r, pow](c::Player& p)
		{
			p.speed += 1;
			r.destroy(pow);
		};
		
		r.assign<c::Position>(pow, glm::vec3(x, y, 0));
		r.assign<c::Lighting>(pow, glm::vec3(0, 1, 0.5), 0.5f);
		r.assign<c::Powerup>(pow, effect);
		r.assign<c::Model>(pow, "block", glm::mat4(1));
		
		r.destroy(e);
	};
	
	r.assign<c::Model>(e, "crate", random_direction());
	r.assign<c::Collide>(e, 10);
	r.assign<c::Position>(e, glm::vec3(x, y, 0));
	r.assign<c::Vulnerable>(e, crateDestruction, 10);
}

static void spawn_col(entt::DefaultRegistry &r, std::string type, int x, int y)
{
	auto wall = r.create();
	glm::mat4 rot(1);
	r.assign<c::Model>(wall, type, random_direction());
	r.assign<c::Collide>(wall, 20);
	r.assign<c::Position>(wall, glm::vec3(x, y, 0));
}

static void spawn_floor(entt::DefaultRegistry& r, int x, int y)
{
	auto floor = r.create();
	r.assign<c::Model>(floor, "floor", glm::mat4(1));
	r.assign<c::Position>(floor, glm::vec3(x, y, 0));
}

void spawn_static_lights(entt::DefaultRegistry &r)
{
	auto light = r.create();
	r.assign<c::Position>(light, glm::vec3(0, 0, 20));
	r.assign<c::Lighting>(light, glm::vec3(1.3, 1.3, 1.3), 10000.0f);
}

void	generate_level(entt::DefaultRegistry &r, int w, int h, ParticleExplosion *expl)
{
	w /= 2;
	h /= 2;

	static std::mt19937 rng;

	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> should_crate(0, 10);

	for (int x = -w; x < w + 1; ++x)
	{
		spawn_wall(r, "block", x, -h);
		spawn_wall(r, "block", x, h);
	}
	for (int y = -h + 1; y < h; ++y)
	{
		spawn_wall(r, "block", w, y);
		spawn_wall(r, "block", -w, y);
	}
	for (int x = -w + 1; x < w; ++x)
	{
		for (int y = -h + 1; y < h; ++y)
		{
			if (abs(x % 2) + abs(y % 2) == 0)
			{
				spawn_col(r, "rock", x, y);
			}
			else
			{
				if (should_crate(rng) == 0)
					spawn_crate(r, x, y, expl);
			}
			spawn_floor(r, x, y);
		}
	}
	spawn_player(r, -w + 1, -h + 1);
	spawn_static_lights(r);
}
