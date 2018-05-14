#include "Cells.hpp"

namespace c = components;

static inline uint64_t hash(float x, float y)
{
	int a = round(x);
	int b = round(y);
	return ((uint64_t)a) << 32 | (uint32_t)b;
}

namespace systems
{

int	Cells::Collision(entt::DefaultRegistry& r, float x, float y)
{
	auto entities = getEntities(x, y);
	int max_height = 0;
	for (auto e : entities)
		if (r.valid(e) && r.has<c::Collide>(e))
			max_height= std::max(r.get<c::Collide>(e).height, max_height);
	return max_height;
}

int	Cells::Danger(entt::DefaultRegistry& r, float x, float y)
{
	auto entities = getEntities(x, y);
	int max_danger = 0;
	for (auto e : entities)
		if (r.valid(e) && r.has<c::Dangerous>(e))
			max_danger= std::max(r.get<c::Dangerous>(e).dangerLevel, max_danger);
	return max_danger;
}

bool Cells::Vulnerable(entt::DefaultRegistry& r, float x, float y)
{
	auto entities = getEntities(x, y);
	for (auto e : entities)
		if (r.valid(e) && r.has<c::Vulnerable>(e))
			return true;
	return false;
}

script Cells::Powerup(entt::DefaultRegistry& r, float x, float y)
{
	auto entities = getEntities(x, y);
	for (auto e : entities)
		if (r.valid(e) && r.has<c::Powerup>(e))
			return r.get<c::Powerup>(e).effect;
	return [](entt::DefaultRegistry&, uint32_t){};
}

std::vector<uint32_t>& Cells::getEntities(float x, float y)
{
	return _map[hash(x, y)];
}

void	Cells::operator()(entt::DefaultRegistry& r)
{
	_map.clear();
	r.view<c::Position>().each([this](auto entity, auto& p){
		_map[hash(p.pos.x, p.pos.y)].push_back(entity);
	});
}

}
