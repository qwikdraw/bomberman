#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "voxGL.hpp"

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

	Camera(void);

	void	Move(glm::vec3 amount);
	void	MoveTo(glm::vec3 position);
	void	RelativeMove(glm::vec3 amount);
	void	Rotate(glm::vec3 axis, float degrees);
	void	SetAspect(float aspect);
	void	SetNearDist(float dist);
	void	SetFarDist(float dist);
	void	SetFOV(float degrees);
	
	glm::mat4	Perspective(void);
	std::pair<glm::mat4, glm::mat4>	ExplicitPerspective(void);
};

#endif
