#pragma once

#include "bomberman.hpp"

class	IParticle
{
protected:
	IParticle() {}
	
public:
	virtual ~IParticle(void) {};
	virtual void	Render(std::pair<glm::mat4, glm::mat4> perspective,
			       glm::vec3 position,
			       float dt) = 0;	
};
