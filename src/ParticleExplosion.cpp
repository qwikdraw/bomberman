
#include "ParticleExplosion.hpp"

#define PARTICLE_AMOUNT 1000

ParticleExplosion::ParticleExplosion(float duration) : _particles(Particles(PARTICLE_AMOUNT)),
						       _duration(duration)
{
	_velocity.resize(PARTICLE_AMOUNT);
	_colors.resize(PARTICLE_AMOUNT);
	_startPos.resize(PARTICLE_AMOUNT);

	for (auto &v : _velocity)
	{
		v = glm::ballRand(1.0f) * glm::linearRand(0.2f, 0.8f);
		v.z *= 10;
	}

	for (auto &p : _startPos)
	{
		p = glm::linearRand(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.5, 0.5, 0.5));
	}

	glm::vec3 col2(0.95, 0.84, 0.23);
	glm::vec3 col1(0.44, 0.16, 0.12);
	glm::vec3 dif = col2 - col1;
	 
	for (size_t i = 0; i < _colors.size(); i++)
	{
		float distFromCenter = length(_startPos[i]) / 0.866;
		_colors[i] = distFromCenter * dif + col1;
	}
}

void	ParticleExplosion::Render(std::pair<glm::mat4, glm::mat4> perspective,
			  glm::vec3 position,
			  float time)
{
	_particles.UseExplicitPerspective(perspective);

	auto &physicalAttrib = _particles.GetPhysicalAttributes();
	auto &colorAttrib = _particles.GetColorAttributes();

	for (size_t i = 0; i < physicalAttrib.size(); i += 4)
	{
		glm::vec3 endPos = _velocity[i / 4] * time / _duration + _startPos[i / 4] + position;
		
		physicalAttrib[i] = endPos.x;
		physicalAttrib[i + 1] = endPos.y;
		physicalAttrib[i + 2] = endPos.z;
		physicalAttrib[i + 3] = 0.1 - ( time / _duration ) * 0.05;
	}
	for (size_t i = 0; i < colorAttrib.size(); i += 4)
	{
		glm::vec3 col = _colors[i / 4] * (_duration - time * 0.8) / (_duration);
		
		colorAttrib[i] = col.x;
		colorAttrib[i + 1] = col.y;
		colorAttrib[i + 2] = col.z;
		colorAttrib[i + 3] = 0.5 - ( time / _duration ) * 0.5;
	}
	_particles.Sort();
	_particles.Update();
	_particles.Render();
}
