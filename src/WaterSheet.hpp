#pragma once

#include "IParticle.hpp"
#include "Particles.hpp"
#include "bomberman.hpp"

class	WaterSheet : public IParticle
{
	Particles _particles;
	std::vector<float> _sync;
	std::vector<glm::vec3> _colors;
	std::vector<glm::vec3> _startPos;
	size_t _amount;

public:

	WaterSheet(float width, float height);

	void	Render(std::pair<glm::mat4, glm::mat4> perspective,
		       glm::vec3 position,
		       float time);
};
