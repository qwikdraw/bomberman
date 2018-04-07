#include "voxGL.hpp"

Time::Time(void)
{
	_oldTime = glfwGetTime();
	_deltaTime = 0.0;
}

void	Time::Step(void)
{
	double time = glfwGetTime();
	_deltaTime = time - _oldTime;
	_oldTime = time;
}

void	Time::Reset(void)
{
	glfwSetTime(0.0);
	_oldTime = 0.0;
}

double	Time::Total(void)
{
	return glfwGetTime();
}

double	Time::Delta(void)
{
	return _deltaTime;
}
