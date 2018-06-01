#pragma once

#include "bomberman.hpp"
#include "ParticleExplosion.hpp"
#include "WaterSheet.hpp"

struct	Effects
{
	static ParticleExplosion *explosion;
	static WaterSheet *water;
	
	static void	CleanUp(void);
};
