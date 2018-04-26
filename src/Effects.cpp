#include "Effects.hpp"

ParticleExplosion *Effects::explosion = nullptr;

void	Effects::CleanUp(void)
{
	delete explosion;
	explosion = nullptr;
}
