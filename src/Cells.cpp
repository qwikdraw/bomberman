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

void	systems::Cells::Update(entt::DefaultRegistry& registry)
{
	_collisionHeight.clear();
	_dangerLevel.clear();

	auto collidables = registry.view<c::Collide, c::Position>();
	auto dangerous = registry.view<c::Dangerous, c::Position>();
	int32_t xi, yi;
	
	for (auto entity : collidables)
	{
		glm::vec3& pos = collidables.get<c::Position>(entity).pos;
		int height = collidables.get<c::Collide>(entity).height;
		uint64_t key;
		
		xi = round(pos.x);
		yi = round(pos.y);
		std::memmove(&key, &yi, 4);
		std::memmove((uint32_t*)(&key) + 1, &xi, 4);
		if (_collisionHeight.count(key) > 0)
			_collisionHeight[key] = std::max(_collisionHeight[key], height);
		else
			_collisionHeight[key] = height;
	}

	for (auto entity : dangerous)
	{
		glm::vec3& pos = dangerous.get<c::Position>(entity).pos;
		int dangerLevel = dangerous.get<c::Dangerous>(entity).dangerLevel;
		uint64_t key;

		xi = round(pos.x);
		yi = round(pos.y);
		std::memmove(&key, &yi, 4);
		std::memmove((uint32_t*)(&key) + 1, &xi, 4);
		if (_dangerLevel.count(key) > 0)
			_dangerLevel[key] = std::max(_dangerLevel[key], dangerLevel);
		else
			_dangerLevel[key] = dangerLevel;
	}
}
