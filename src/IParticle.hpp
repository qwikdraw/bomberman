#pragma once

#include "bomberman.hpp"

//! An interface for particle systems
class	IParticle
{
protected:
	IParticle() {}
	
public:
	virtual ~IParticle(void) {};
	//! the camera angle, the position and the time elapsed
	virtual void	Render(std::pair<glm::mat4, glm::mat4> perspective,
			       glm::vec3 position,
			       float time) = 0;	
};
