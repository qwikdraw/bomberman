#pragma once

#include "bomberman.hpp"
#include "components.hpp"
#include <unordered_map>
#include <cstdint>

namespace c = components;

namespace systems
{
	class	Cells
	{
		std::unordered_map<uint64_t, int> _collisionHeight;
		std::unordered_map<uint64_t, int> _dangerLevel;
		std::unordered_map<uint64_t, std::function<void(c::Player&)> > _powerup;

	public:

		int	Collision(float x, float y);
		int	Danger(float x, float y);
		std::function<void(c::Player&)>	Powerup(float x, float y);
		void	Update(entt::DefaultRegistry&);
	};
}
