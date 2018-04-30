#include "Cells.hpp"

namespace c = components;

namespace systems
{

int	Cells::Collision(float x, float y)
{
	uint64_t key;
	uint32_t xi = (uint32_t)round(x);
	uint32_t yi = (uint32_t)round(y);
	key = ((uint64_t)xi) << 32 | yi;
	if (_collisionHeight.count(key) == 0)
		return 0;
	return _collisionHeight[key];
}

int	Cells::Danger(float x, float y)
{
	uint64_t key;
	uint32_t xi = (uint32_t)round(x);
	uint32_t yi = (uint32_t)round(y);
	key = ((uint64_t)xi) << 32 | yi;
	if (_dangerLevel.count(key) == 0)
		return 0;
	return _dangerLevel[key];
}

systems::powerType	Cells::Powerup(float x, float y)
{
	uint64_t key;
	uint32_t xi = (uint32_t)round(x);
	uint32_t yi = (uint32_t)round(y);
	key = ((uint64_t)xi) << 32 | yi;
	if (_powerup.count(key) == 0)
	{
		powerType doNothing = [](entt::DefaultRegistry&, uint32_t){};
		return doNothing;
	}
	return _powerup[key];
}

void	Cells::Update(entt::DefaultRegistry& registry)
{
	_collisionHeight.clear();
	_dangerLevel.clear();
	_powerup.clear();

	uint32_t xi, yi;
	uint64_t key;
	
	auto collidables = registry.view<c::Collide, c::Position>();
	for (auto entity : collidables)
	{
		glm::vec3& pos = collidables.get<c::Position>(entity).pos;
		int height = collidables.get<c::Collide>(entity).height;
		
		xi = (uint32_t)round(pos.x);
		yi = (uint32_t)round(pos.y);
		key = ((uint64_t)xi) << 32 | yi;
		if (_collisionHeight.count(key) > 0)
			_collisionHeight[key] = std::max(_collisionHeight[key], height);
		else
			_collisionHeight[key] = height;
	}
	
	auto dangerous = registry.view<c::Dangerous, c::Position>();	
	for (auto entity : dangerous)
	{
		glm::vec3& pos = dangerous.get<c::Position>(entity).pos;
		int dangerLevel = dangerous.get<c::Dangerous>(entity).dangerLevel;

		xi = (uint32_t)round(pos.x);
		yi = (uint32_t)round(pos.y);
		key = ((uint64_t)xi) << 32 | yi;
		if (_dangerLevel.count(key) > 0)
			_dangerLevel[key] = std::max(_dangerLevel[key], dangerLevel);
		else
			_dangerLevel[key] = dangerLevel;
	}

	auto powerups = registry.view<c::Powerup, c::Position>();
	for (auto entity : powerups)
	{
		glm::vec3& pos = powerups.get<c::Position>(entity).pos;
		auto& effect = powerups.get<c::Powerup>(entity).effect;
		
		xi = (uint32_t)round(pos.x);
		yi = (uint32_t)round(pos.y);
		key = ((uint64_t)xi) << 32 | yi;
		_powerup[key] = effect;
	}
}

}
