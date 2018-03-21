#ifndef WINDOW_CLASS_HPP
#define WINDOW_CLASS_HPP

#include "voxGL.hpp"

//! Application window
/*!
Currently windows represent an application window
and the ability to specify a subsection that application window
for rendering.
All coordinates are in normalized device coordinates.
*/
class	Window
{
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
	void	RefreshStencil(void);

public:
	//! Create a new window with x width and y height the window title is set to name.
	Window(int x, int y, std::string name);

	//! Gets the size of the application window
	/*!
	This function gets the size of the application window regardless of the current stencil.
	Fills arguments with the result.
	For the size of the currently drawable area (with respect to the current stencil), see GetDrawableSize.
	*/
	void	GetSize(float &width, float &height);
	
	//! Returns true if the window is open, false otherwise.
	bool	IsOpen(void);

	//! Set a rendering stencil.
	/*! Specify the area of the window you wish to draw to. (x, y) is the coordinate of the bottom left part
	of the rectangle you wish to draw to. Width and height define the rectangle that will be drawable with
	its lower left corner at that point.
	Implemented with glStencil.
	*/
	void	SetStencil(float x, float y, float width, float height);

	//! Removes render stencil.
	void	ClearStencil(void);

	//! Get the current drawable area, value depends on the current stencil
	void	GetDrawableSize(float &width, float &height);

	//! Clears render zone with the current glClearColor.
	void	Clear(void);
	
	//! Renders entire window, call once per frame.
	void	Render(void);
	
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
