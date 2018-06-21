#pragma once

#include "bomberman.hpp"
#include "components.hpp"
#include <unordered_map>
#include <cstdint>

namespace c = components;

namespace systems
{
	//! The Cell class
	
	class	Cells
	{
		std::unordered_map<uint64_t, std::vector<uint32_t>> _map;
	public:
		//! returns max height of collision of all entities at position (x, y)
		int Collision(entt::DefaultRegistry&, float x, float y);
		//! returns max danger of all entities at position (x, y)
		int Danger(entt::DefaultRegistry&, float x, float y);
		//! returns vulnerability of all entities at position (x, y)
		bool Vulnerable(entt::DefaultRegistry& r, float x, float y);
		//! return powerup effect of valid powerup at position (x, y)
		scripts::script Powerup(entt::DefaultRegistry&, float x, float y);
		//! returns a vector containing all entities at position (x, y)
		std::vector<uint32_t>& getEntities(float x, float y);
		void operator() (entt::DefaultRegistry&);
	};
}
