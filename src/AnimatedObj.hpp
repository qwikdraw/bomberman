#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ObjFile.hpp"
#include "Time.hpp"

class	AnimatedObject
{
public:
	struct	AnimatedPartRaw
	{
		std::string objectFile;
		std::string textureFile;
		std::vector<glm::mat4> transform;
		std::vector<float> time;
		float cycle;
		glm::vec3 pos;
	};
	
private:
	struct	AnimatedPart
	{
		ObjFile *object;
		std::vector<glm::mat4> animaTransform;
		std::vector<float> animaTime;
		float animaCycle;
		glm::vec3 partPos;
	};
	
private:

	Time _time;
	std::vector<AnimatedPart> _parts;
	float _totalTime;
	std::pair<glm::mat4, glm::mat4> _perspective;
	glm::mat4 _transform;
	glm::vec3 _pos;

	
	glm::mat4	InterpolateMatrix(AnimatedPart part);

public:

	AnimatedObject(std::string filepath);
	~AnimatedObject(void);
	void	UsePerspective(std::pair<glm::mat4, glm::mat4>);
	void	SetTransform(glm::mat4);
	void	Move(glm::vec3);
	void	MoveTo(glm::vec3);
	void	Render(void);
};

std::istream	&operator >> (std::istream &is, AnimatedObject::AnimatedPartRaw &lhs);
