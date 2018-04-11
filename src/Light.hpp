#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "voxGL.hpp"

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
	
	Light(glm::vec3 pos, glm::vec3 color, float falloff);
	~Light(void);
};

#endif
