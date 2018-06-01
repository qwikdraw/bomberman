#include "Effects.hpp"

ParticleExplosion *Effects::explosion = nullptr;
Sparkles *Effects::sparkles = nullptr;

void	Effects::CleanUp(void)
{
	delete explosion;
	explosion = nullptr;
	delete sparkles;
	sparkles = nullptr;
}
