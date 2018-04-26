#include "Cells.hpp"

namespace c = components;

int	systems::Cells::Collision(float x, float y)
{
	int32_t xi, yi;
	uint64_t key;
	xi = round(x);
	yi = round(y);
	std::memmove(&key, &yi, 4);
	std::memmove((uint32_t*)(&key) + 1, &xi, 4);
	
	if (_collisionHeight.count(key) == 0)
		return 0;
	return _collisionHeight[key];
}

int	systems::Cells::Danger(float x, float y)
{
	int32_t xi, yi;
	uint64_t key;	
	xi = round(x);
	yi = round(y);
	std::memmove(&key, &yi, 4);
	std::memmove((uint32_t*)(&key) + 1, &xi, 4);
	
	if (_dangerLevel.count(key) == 0)
		return 0;
	return _dangerLevel[key];
}

systems::powerType	systems::Cells::Powerup(float x, float y)
{
	int32_t xi, yi;
	uint64_t key;
	xi = round(x);
	yi = round(y);
	std::memmove(&key, &yi, 4);
	std::memmove((uint32_t*)(&key) + 1, &xi, 4);

	if (_powerup.count(key) == 0)
	{
		powerType doNothing = [](entt::DefaultRegistry&, uint32_t, c::Player&){};
		return doNothing;
	}
	return _powerup[key];
}

void	systems::Cells::Update(entt::DefaultRegistry& registry)
{
	_collisionHeight.clear();
	_dangerLevel.clear();
	_powerup.clear();

	int32_t xi, yi;
	uint64_t key;
	
	auto collidables = registry.view<c::Collide, c::Position>();
	for (auto entity : collidables)
	{
		glm::vec3& pos = collidables.get<c::Position>(entity).pos;
		int height = collidables.get<c::Collide>(entity).height;
		
		xi = round(pos.x);
		yi = round(pos.y);
		std::memmove(&key, &yi, 4);
		std::memmove((uint32_t*)(&key) + 1, &xi, 4);
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

		xi = round(pos.x);
		yi = round(pos.y);
		std::memmove(&key, &yi, 4);
		std::memmove((uint32_t*)(&key) + 1, &xi, 4);
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
		
		xi = round(pos.x);
		yi = round(pos.y);
		std::memmove(&key, &yi, 4);
		std::memmove((uint32_t*)(&key) + 1, &xi, 4);
		_powerup[key] = effect;
	}
}
