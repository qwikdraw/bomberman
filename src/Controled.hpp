#ifndef CONTROLED_HPP
#define CONTROLED_HPP

#include "Window.hpp"

class	Controled
{

	Window &_window;
	glm::vec3 _pos;
	float _speed;
	
public:

struct KeyBind
{
	int up;
	int down;
	int left;
	int right;
};
	
	static KeyBind keyBind;
	
	Controled(Window&, float speed = 1);

	glm::vec3	Position(void);
	
	void	Update(double dt);
	void	SetSpeed(float speed);
	void	Move(glm::vec3);
	void	MoveTo(glm::vec3);
};

#endif
