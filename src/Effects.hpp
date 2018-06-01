#pragma once

#include "bomberman.hpp"
#include "ParticleExplosion.hpp"
#include "Sparkles.hpp"

struct	Effects
{
	static ParticleExplosion *explosion;
	static Sparkles *sparkles;
	
	static void	CleanUp(void);
};
