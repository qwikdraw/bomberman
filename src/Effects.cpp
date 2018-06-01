#include "Effects.hpp"

ParticleExplosion *Effects::explosion = nullptr;
WaterSheet *Effects::water = nullptr;

void	Effects::CleanUp(void)
{
	delete explosion;
	explosion = nullptr;
	delete water;
	water = nullptr;
}
