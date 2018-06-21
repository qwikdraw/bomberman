#pragma once

#include "bomberman.hpp"
#include "ParticleExplosion.hpp"
#include "Sparkles.hpp"

//! stores global instances of various concrete particle systems
struct	Effects
{
	static ParticleExplosion *explosion;
	static Sparkles *sparkles;
	
	//! cleans up the instances
	static void	CleanUp(void);
};
