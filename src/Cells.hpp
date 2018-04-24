#pragma once

#include "bomberman.hpp"
#include "components.hpp"
#include <unordered_map>
#include <cstdint>

namespace systems
{
	class	Cells
	{
		std::unordered_map<uint64_t, int> _collisionHeight;
		std::unordered_map<uint64_t, int> _dangerLevel;

	public:

		int	Collision(float x, float y);
		int	Danger(float x, float y);
		void	Update(entt::DefaultRegistry&);
	};
}
