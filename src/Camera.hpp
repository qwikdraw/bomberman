#pragma once

#include "bomberman.hpp"

class	Camera
{
private:

	static glm::vec3 constexpr _basePos = {0, 0, 0};
	static glm::vec3 constexpr _up = {0, 0, 1};
	static glm::vec3 constexpr _forward = {1, 0, 0};

	glm::vec3 _position;
	glm::mat4 _rotation;
	float _aspect;
	float _near;
	float _far;
	float _fov;

public:

	//! Create a camera used for getting perspectives.
	/*!
	the following values are initialized:
	Aspect ratio = 1, near dist = 0.1, far dist = 1000, fov = 45 degrees. The camera starts facing
	the positive X axis at the origin with (0, 0, 1) being its up vector.
	 */	
	Camera(void);

	void	Move(glm::vec3 amount);
	void	MoveTo(glm::vec3 position);
	void	RelativeMove(glm::vec3 amount);
	void	Rotate(glm::vec3 axis, float degrees);
	void	SetAspect(float aspect);
	void	SetNearDist(float dist);
	void	SetFarDist(float dist);
	void	SetFOV(float degrees);
	
	std::pair<glm::mat4, glm::mat4>	Perspective(void);
};
