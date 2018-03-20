
#include "voxGL.hpp"

Time::Time(void)
{
	_startTime = std::chrono::high_resolution_clock::now();
	_delta = _startTime;
	_totalTime = 0;
	_deltaTime = -1;
}

void	Time::Fix(void)
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto elapsedTime = currentTime - _startTime;
	auto elapsedDeltaTime = currentTime - _delta;

	_totalTime = std::chrono::duration<float>(elapsedTime).count();

	if (_deltaTime != -1)
		_deltaTime = std::chrono::duration<float>(elapsedDeltaTime).count();
	else
		_deltaTime = 0;

	_delta = std::chrono::high_resolution_clock::now();
}

void	Time::Reset(void)
{
	_startTime = std::chrono::high_resolution_clock::now();
	_delta = _startTime;
	_totalTime = 0;
	_deltaTime = -1;
}

float	Time::GetTime(void)
{
	return _totalTime;
}

float	Time::GetDeltaTime(void)
{
	return _deltaTime;
}
