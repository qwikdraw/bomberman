
#include "Controled.hpp"

Controled::KeyBind Controled::keyBind = {'W', 'S', 'A', 'D'};

Controled::Controled(Window &window, float speed) : _window(window),
						    _speed(speed)
{
	_pos = glm::vec3(0, 0, 0);
}

glm::vec3	Controled::Position(void)
{
	return _pos;
}

void	Controled::Update(double dt)
{
	if (_window.Key(keyBind.up))
		_pos.y += _speed * dt;
	if (_window.Key(keyBind.down))
		_pos.y -= _speed * dt;
	if (_window.Key(keyBind.left))
		_pos.x -= _speed * dt;
	if (_window.Key(keyBind.right))
		_pos.x += _speed * dt;
}

void	Controled::SetSpeed(float speed)
{
	_speed = speed;
}

void	Controled::Move(glm::vec3 amount)
{
	_pos += amount;
}

void	Controled::MoveTo(glm::vec3 pos)
{
	_pos = pos;
}
