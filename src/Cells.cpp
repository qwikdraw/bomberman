#include "Cells.hpp"

namespace c = components;

namespace systems
{

static uint64_t	keyHash(float x, float y)
{
	uint64_t key;
	int32_t ix = round(x);
	int32_t iy = round(y);

	std::memmove(&key, &iy, sizeof(int32_t));
	std::memmove((int32_t*)&key + 1, &ix, sizeof(int32_t));
	return key;
}
	
int	Cells::Collision(float x, float y)
{
	uint64_t key = keyHash(x, y);
	
	if (_collisionHeight.count(key) == 0)
		return 0;
	return _collisionHeight[key];
}

int	Cells::Danger(float x, float y)
{
	uint64_t key = keyHash(x, y);
	
	if (_dangerLevel.count(key) == 0)
		return 0;
	return _dangerLevel[key];
}

systems::powerType	Cells::Powerup(float x, float y)
{
	uint64_t key = keyHash(x, y);

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

	uint64_t key;
	
	auto collidables = registry.view<c::Collide, c::Position>();
	for (auto entity : collidables)
	{
		glm::vec3& pos = collidables.get<c::Position>(entity).pos;
		int height = collidables.get<c::Collide>(entity).height;

		key = keyHash(pos.x, pos.y);

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

		key = keyHash(pos.x, pos.y);

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

		key = keyHash(pos.x, pos.y);

		_powerup[key] = effect;
	}
}

}
