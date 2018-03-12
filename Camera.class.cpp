
#include "voxGL.hpp"

glm::vec3 const	Camera::Pos;
glm::vec3 const	Camera::Up;
glm::vec3 const	Camera::Forward;
glm::vec3 const	Camera::Right;

Camera::Camera(void) : _cameraShouldMove(true)
{
	_transform = glm::mat4(1);
}

glm::mat4	Camera::Perspective(void)
{
	glm::mat4 look = glm::lookAt(glm::vec3(_transform * glm::vec4(Pos, 1)),
				     glm::vec3(_transform * glm::vec4(Forward, 1)),
				     glm::vec3(_transform * glm::vec4(Up, 0)));

	float width, height;

	_window->GetSize(width, height);

	glm::mat4 perspective = glm::perspective(glm::radians(45.0f), width/height, 0.1f, 1000.0f);

	return perspective * look;
}

void	Camera::Move(glm::vec3 amount)
{
	_transform = glm::translate(_transform, amount);
	_cameraShouldMove = true;
}

void	Camera::Rotate(glm::vec3 axis, float degrees)
{
	_transform = glm::rotate(_transform, glm::radians(degrees), axis);
	_cameraShouldMove = true;	
}

void	Camera::TrackEvents(Window *window)
{
	_window = window;
}

void	Camera::Update(void)
{
	_time.Fix();

	if (_window->IsForward())
	{
		Move(Forward * _time.GetDeltaTime() * 10);
	}
	if (_window->IsBackward())
	{
		Move(-Forward * _time.GetDeltaTime() * 10);
	}
	if (_window->IsLeft())
	{
		Move(-Right * _time.GetDeltaTime() * 10);
	}
	if (_window->IsRight())
	{
		Move(Right * _time.GetDeltaTime() * 10);
	}
	if (_window->IsUp())
	{
		Move(Up * _time.GetDeltaTime() * 10);		
	}
	if (_window->IsDown())
	{
		Move(-Up * _time.GetDeltaTime() * 10);
	}
	if (_window->KeyOn('N'))
	{
		Rotate(glm::vec3(0, -1, 0), _time.GetDeltaTime() * 10);
	}
	if (_window->KeyOn('M'))
	{
		Rotate(glm::vec3(0, 1, 0), _time.GetDeltaTime() * 10);
	}
	if (_window->KeyOn('J'))
	{
		Rotate(glm::vec3(-1, 0, 0), _time.GetDeltaTime() * 10);
	}
	if (_window->KeyOn('K'))
	{
		Rotate(glm::vec3(1, 0, 0), _time.GetDeltaTime() * 10);
	}
}

bool	Camera::JustMoved(void)
{
	bool out = _cameraShouldMove;
	_cameraShouldMove = false;
	return out;
}
