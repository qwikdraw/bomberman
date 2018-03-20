#ifndef CAMERA_CLASS_HPP
#define CAMERA_CLASS_HPP

#include "voxGL.hpp"

class	Camera
{
private:

	Time _time;
	glm::mat4 _transform;
	Window *_window;
	bool _cameraShouldMove;
	
public:

	static const glm::vec3 constexpr Pos = {0, 0, 0};
	static const glm::vec3 constexpr Up = {0, 1, 0};
	static const glm::vec3 constexpr Forward = {0, 0, 1};
	static const glm::vec3 constexpr Right = {1, 0, 0};

	Camera(void);
	
	void	Move(glm::vec3 amount);
	void	Rotate(glm::vec3 axis, float degrees);
	void	TrackEvents(Window*);
	void	Update(void);
	bool	JustMoved(void);
	glm::mat4	Perspective(void);
};

#endif
