
#include "ParticleExplosion.hpp"

ParticleExplosion::ParticleExplosion(float duration) : _particles(Particles(1000)), _duration(duration)
{
	_velocity.resize(1000);

	for (auto &v : _velocity)
	{
		v = glm::ballRand(1.0f) * glm::linearRand(0.2f, 0.5f);
	}
}

void	ParticleExplosion::Render(std::pair<glm::mat4, glm::mat4> perspective,
			  glm::vec3 position,
			  float time)
{
	_particles.UseExplicitPerspective(perspective);

	auto &physicalAttrib = _particles.GetPhysicalAttributes();
	auto &colorAttrib = _particles.GetColorAttributes();
	glm::vec3 center = position + glm::vec3(0, 0, 0.5);

	for (size_t i = 0; i < physicalAttrib.size(); i += 4)
	{
		glm::vec3 endPos = _velocity[i / 4] * time + center;
		
		physicalAttrib[i] = endPos.x;
		physicalAttrib[i + 1] = endPos.y;
		physicalAttrib[i + 2] = endPos.z;
		physicalAttrib[i + 3] = 0.2;
	}
	for (size_t i = 0; i < colorAttrib.size(); i += 4)
	{
		colorAttrib[i] = 0.8;
		colorAttrib[i + 1] = 0.2;
		colorAttrib[i + 2] = 0.2;
		colorAttrib[i + 3] = (_duration - time) / _duration;
	}
	_particles.Sort();
	_particles.Update();
	_particles.Render();
}
