#include <random>
#include <deque>
#include "bomberman.hpp"
#include "build_level.hpp"

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

static std::function<void(entt::DefaultRegistry& r, int x, int y)> spawn[128] = {

	['#'] = [](entt::DefaultRegistry &r, int x, int y)
	{
		auto wall = r.create();
		r.assign<c::Model>(wall, "block", glm::mat4(1));
		r.assign<c::Collide>(wall, 100000);
		r.assign<c::Position>(wall, glm::vec3(x, y, 0));
	},

	['+'] = [](entt::DefaultRegistry &r, int x, int y)
	{
		auto column = r.create();
		glm::mat4 rot(1);
		r.assign<c::Model>(column, "rock", random_direction());
		r.assign<c::Collide>(column, 20);
		r.assign<c::Position>(column, glm::vec3(x, y, 0));
	},

	['c'] = [](entt::DefaultRegistry &r, int x, int y)
	{
		auto e = r.create();

		r.assign<c::Model>(e, "crate", random_direction());
		r.assign<c::Collide>(e, 10);
		r.assign<c::Position>(e, glm::vec3(x, y, 0));
		r.assign<c::Vulnerable>(e,
			scripts::powerup(0.5) +
			scripts::destroy(),
			10
		);
	},

	['>'] = [](entt::DefaultRegistry &r, int x, int y)
	{
		auto enemy = r.create();
		r.assign<c::Position>(enemy, glm::vec3(x, y, 0));
		r.assign<c::Model>(enemy, "enemy", glm::mat4(1));
		r.assign<c::Velocity>(enemy);
		r.assign<c::Collide>(enemy, 5);
		r.assign<c::AI>(enemy, 2.0, 1.0, c::AI_type::HORZ);
		r.assign<c::Dangerous>(enemy, 10);
		r.assign<c::Vulnerable>(enemy, scripts::destroy(), 11);
	},

	['^'] = [](entt::DefaultRegistry &r, int x, int y)
	{
		auto enemy = r.create();
		r.assign<c::Position>(enemy, glm::vec3(x, y, 0));
		r.assign<c::Model>(enemy, "enemy", glm::mat4(1));
		r.assign<c::Velocity>(enemy);
		r.assign<c::Collide>(enemy, 5);
		r.assign<c::AI>(enemy, 2.0, 1.0, c::AI_type::VERT);
		r.assign<c::Dangerous>(enemy, 10);
		r.assign<c::Vulnerable>(enemy, scripts::destroy(), 11);
	}
};


void	build_level(entt::DefaultRegistry &r, Engine& engine, std::string level)
{
	// Engine Tag for scripts
	auto e = r.create();
	r.assign<c::EngineTag>(entt::tag_t{}, e, engine);

	// Global Lighting
	auto light = r.create();
	r.assign<c::Position>(light, glm::vec3(0, 0, 20));
	r.assign<c::Lighting>(light, glm::vec3(1.3, 1.3, 1.3), 10000.0f);

	// Read level data
	std::ifstream file(ASSET_PATH "levels/" + level + ".lvl");
	std::deque<std::string> level_data;
	std::string line;
	std::string next_level;
	std::string baseplate;
	std::getline(file, next_level);
	spawn[(int)'g'] = [next_level](entt::DefaultRegistry &r, int x, int y)
	{
		auto goal = r.create();
		r.assign<c::Position>(goal, glm::vec3(x, y, 0));
		r.assign<c::Model>(goal, "flag", glm::mat4(1));
		r.assign<c::Powerup>(goal, scripts::switch_level(next_level));
	};
	spawn[(int)'p'] = [level](entt::DefaultRegistry &r, int x, int y)
	{
		auto player = r.create();
		r.assign<c::Player>(entt::tag_t{}, player, 2.0, 1.0);
		r.assign<c::Model>(player, "player", glm::mat4(1));
		r.assign<c::Position>(player, glm::vec3(x, y, 0));
		r.assign<c::Velocity>(player);
		r.assign<c::Collide>(player, 5);
		r.assign<c::Vulnerable>(player, scripts::death(level));
	};
	std::getline(file, baseplate);
	while (std::getline(file, line))
		level_data.push_front(line);
	int y = 0;
	int width = 0;
	for (auto& row : level_data)
	{
		int x = 0;
		for (auto& piece : row)
		{
			if (spawn[(int)piece])
				spawn[(int)piece](r, x, y);
			++x;
			if (x > width)
				width = x;
		}
		++y;
	}

	// Baseplate
	auto base = r.create();
	r.assign<c::Position>(base, glm::vec3(width / 2.0, y / 2.0, 0));
	r.assign<c::Model>(base, baseplate, glm::mat4(1));
}
