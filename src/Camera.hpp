#pragma once

#include "bomberman.hpp"

//! Camera class
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

	//! Moves the camera by an amount as specified by a 3D vector
	void	Move(glm::vec3 amount);
	//! Moves the camer to a specified position
	void	MoveTo(glm::vec3 position);
	//! Returns position of camera
	glm::vec3	GetPosition(void);
	//! Moves the camera relative to current position and direction 
	void	RelativeMove(glm::vec3 amount);
	//! Rotates the camera a specified number of degrees along a specified axis 
	void	Rotate(glm::vec3 axis, float degrees);
	//! Sets the camera's aspect ratio
	void	SetAspect(float aspect);
	//! Sets the camera's near distance
	void	SetNearDist(float dist);
	//! Sets the camera's far distance
	void	SetFarDist(float dist);
	//! Sets camera's field of view
	void	SetFOV(float degrees);
	//! Returns perspective
	std::pair<glm::mat4, glm::mat4>	Perspective(void);
};
