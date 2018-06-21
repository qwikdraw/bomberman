#pragma once

#include "bomberman.hpp"

//! For lighting the scene
class	Light
{
private:

	static std::vector<glm::vec3> _positions;
	static std::vector<glm::vec3> _colors;
	static std::vector<float> _falloffs;
	
	glm::vec3 _pos;
	glm::vec3 _color;
	float _falloff;
	
public:

	const static std::vector<glm::vec3> &positions;
	const static std::vector<glm::vec3> &colors;
	const static std::vector<float> &falloffs;

	//! creation adds a light to the scene
	Light(glm::vec3 pos, glm::vec3 color, float falloff);
	//! destruction removes light from the scene
	~Light(void);
};
