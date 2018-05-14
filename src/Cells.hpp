#pragma once

#include "bomberman.hpp"
#include "components.hpp"
#include <unordered_map>
#include <cstdint>

namespace c = components;

typedef std::function<void(entt::DefaultRegistry&, uint32_t)> script;

namespace systems
{
	class	Cells
	{
		std::unordered_map<uint64_t, std::vector<uint32_t>> _map;
	public:
		int Collision(entt::DefaultRegistry&, float x, float y);
		int Danger(entt::DefaultRegistry&, float x, float y);
		bool Vulnerable(entt::DefaultRegistry& r, float x, float y);
		script Powerup(entt::DefaultRegistry&, float x, float y);
		std::vector<uint32_t>& getEntities(float x, float y);
		void operator() (entt::DefaultRegistry&);
	};
}
