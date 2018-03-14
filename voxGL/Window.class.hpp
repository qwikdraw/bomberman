#ifndef WINDOW_CLASS_HPP
#define WINDOW_CLASS_HPP

#include "voxGL.hpp"

class	Window
{
private:


	static void	KeyCallback(GLFWwindow*, int, int, int, int);
	static void	ErrorCallback(int, const char*);
	static void	WindowResizeCallback(GLFWwindow*, int, int);
	static void	WindowMoveCallback(GLFWwindow*, int, int);

	
	GLFWwindow *_window;
	
	bool _keyHeld[4096] = {};
	int _forward;
	int _backward;
	int _left;
	int _right;
	int _up;
	int _down;

	float _screenCornerX;
	float _screenCornerY;
	float _width;
	float _height;
	
	Window(void);

	void	WindowHints(void);
	void	RefreshRenderZone(void);

public:

	Window(int x, int y, std::string name);

	void	GetSize(float &width, float &height);
	bool	IsOpen(void);
	void	GetRenderZoneSize(float &width, float &height);
	void	SetRenderZone(float x, float y, float width, float height);
	void	ClearRenderZone(void);
	void	UpdateEntireWindow(void);
	
	void	EventListen(void);
	bool	&KeyOn(int);
	
	void	ForwardAndBackKeys(int forward, int back);
	void	LeftAndRightKeys(int left, int right);
	void	UpAndDownKeys(int up, int down);
	
	bool	IsForward(void);
	bool	IsBackward(void);
	bool	IsLeft(void);
	bool	IsRight(void);
	bool	IsUp(void);
	bool	IsDown(void);
};

#endif
