#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ObjFile.hpp"
#include "Time.hpp"

//! Used for rendering .model files
class	Model
{
public:
	struct	AnimatedPartRaw
	{
		std::string objectFile;
		std::string textureFile;
		float specular;
		float fog;
		glm::vec3 fogcol;
		float diffuse;
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

	std::vector<AnimatedPart> _parts;
	std::pair<glm::mat4, glm::mat4> _perspective;
	glm::mat4 _transform;
	glm::vec3 _pos;

	
	glm::mat4	InterpolateMatrix(AnimatedPart part, float time);
	
        void    UsePerspective(std::pair<glm::mat4, glm::mat4>);
        void    SetTransform(glm::mat4);
        void    MoveTo(glm::vec3);
	void	Render(float time);
	
public:

	//! Loads the model from the file
	Model(std::string filepath);
	~Model(void);
	//! Renders the model to the current render zone
	/*! perspective is from the camera, transform and position decide where
	the model is rendered, and time decides what cycle of the animation to display	
	 */
	void	Render(std::pair<glm::mat4, glm::mat4> perspective,
		       glm::mat4 transform,
		       glm::vec3 position,
		       float time);
};

std::istream	&operator >> (std::istream &is, Model::AnimatedPartRaw &lhs);
