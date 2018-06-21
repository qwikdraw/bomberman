#pragma once

#include "IParticle.hpp"
#include "Particles.hpp"

//! a type of particle system that looks like an explosion
class	ParticleExplosion : public IParticle
{
private:

	Particles _particles;
	std::vector<glm::vec3> _velocity;
	std::vector<glm::vec3> _colors;
	std::vector<glm::vec3> _startPos;
	float _duration;
	
public:
	ParticleExplosion(float duration);

	void	Render(std::pair<glm::mat4, glm::mat4> perspective,
		       glm::vec3 position,
		       float time);
};
