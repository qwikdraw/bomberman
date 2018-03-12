#ifndef TIME_CLASS_HPP
#define TIME_CLASS_HPP

#include "voxGL.hpp"

class	Time
{
private:
	
	std::chrono::high_resolution_clock::time_point _startTime;
	std::chrono::high_resolution_clock::time_point _delta;
	float _totalTime;
	float _deltaTime;

public:

	Time(void);
	
	void	Fix(void);
	void	Reset(void);
	float GetTime(void);
	float GetDeltaTime(void);
};

#endif
