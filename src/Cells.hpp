#pragma once

#include "bomberman.hpp"
#include "components.hpp"
#include <unordered_map>
#include <cstdint>

namespace c = components;

namespace systems
{
	typedef std::function<void(entt::DefaultRegistry&, uint32_t, c::Player&)> powerType;
	class	Cells
	{
		std::unordered_map<uint64_t, int> _collisionHeight;
		std::unordered_map<uint64_t, int> _dangerLevel;
		std::unordered_map<uint64_t, powerType > _powerup;

	public:

		int	Collision(float x, float y);
		int	Danger(float x, float y);
		powerType	Powerup(float x, float y);
		void	Update(entt::DefaultRegistry&);
	};
}
