#pragma once

#include "IParticle.hpp"
#include "bomberman.hpp"

class	TestParticle : public IParticle
{
public:

	TestParticle(void);
	void	Render(std::pair<glm::mat4, glm::mat4>, glm::vec3, float dt);
};
