#include "Camera.hpp"

glm::vec3 constexpr Camera::_basePos;
glm::vec3 constexpr Camera::_up;
glm::vec3 constexpr Camera::_forward;

Camera::Camera(void)
{
	_position = _basePos;
	_rotation = glm::mat4(1);
	_aspect = 1;
	_near = 0.1;
	_far = 1000;
	_fov = 45;
}

void	Camera::Move(glm::vec3 amount)
{
	_position += amount;
}

void	Camera::MoveTo(glm::vec3 position)
{
	_position = position;
}

void	Camera::RelativeMove(glm::vec3 amount)
{
	glm::vec3 absolute = glm::vec3(_rotation * glm::vec4(amount, 0));

	Move(absolute);
}

void	Camera::Rotate(glm::vec3 axis, float degrees)
{
	_rotation = glm::rotate(_rotation, glm::radians(degrees), axis);
}

void	Camera::SetAspect(float aspect)
{
	_aspect = aspect;
}

void	Camera::SetNearDist(float dist)
{
	_near = dist;
}

void	Camera::SetFarDist(float dist)
{
	_far = dist;
}

void	Camera::SetFOV(float degrees)
{
	_fov = degrees;
}

std::pair<glm::mat4, glm::mat4>	Camera::Perspective(void)
{
	glm::mat4 transform = glm::translate(_rotation, _position);
	glm::mat4 lookAt = glm::lookAt(glm::vec3(transform * glm::vec4(_basePos, 1)),
				       glm::vec3(transform * glm::vec4(_forward, 1)),
				       glm::vec3(transform * glm::vec4(_up, 0)));
	glm::mat4 perspective = glm::perspective(glm::radians(_fov), _aspect, _near, _far);

	return std::pair<glm::mat4, glm::mat4>(lookAt, perspective);
}
