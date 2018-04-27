#pragma once

#include "bomberman.hpp"
#include "ParticleExplosion.hpp"

struct	Effects
{
	static ParticleExplosion *explosion;
	
	static void	CleanUp(void);
};
