#ifndef WINDOW_CLASS_HPP
#define WINDOW_CLASS_HPP

#include "voxGL.hpp"
#include <glm/vec2.hpp>

void	KeyCallback(GLFWwindow*, int key, int, int action, int);
void	MouseButtonCallback(GLFWwindow*, int button, int action, int);
void	MousePositionCallback(GLFWwindow*, double x, double y);
void	WindowResizeCallback(GLFWwindow*, int width, int height);

//! Application window
/*!
Currently windows represent an application window
and the ability to specify a subsection that application window
for rendering.
All coordinates are in normalized device coordinates.
*/
class	Window
{
	friend void	KeyCallback(GLFWwindow*, int key, int, int action, int);
	friend void	MouseButtonCallback(GLFWwindow*, int button, int action, int);
	friend void	MousePositionCallback(GLFWwindow*, double x, double y);
	friend void	WindowResizeCallback(GLFWwindow*, int width, int hieght);
	static void	ErrorCallback(int, const char*);
	static void	WindowMoveCallback(GLFWwindow*, int, int);
	GLFWwindow* _window;

	float _screenCornerX;
	float _screenCornerY;
	float _width;
	float _height;
	int _window_width;
	int _window_height;

	void	WindowHints(void);
	void	RefreshRenderMask(void);

	//! Array of bools indicating if a key is down.
	bool _keys[512] = {false};

	//! Array of bools indicating if a mouse button is pressed.
	bool _mouseButtons[8] = {false};

	glm::vec2 _mousePosition = glm::vec2(0.0f, 0.0f);
public:

	//! Create a new window with x width and y height the window title is set to name.
	Window(int x, int y, std::string name);

	//! Gets the size of the application window
	/*!
	This function gets the size of the application window regardless of the current stencil.
	Fills arguments with the result.
	For the size of the currently drawable area (with respect to the current stencil), see GetDrawableSize.
	*/
	void	GetMaxRenderSize(float &width, float &height);
	void	GetWindowSize(float &width, float &height);

	//! Gets the aspect ratio of the currently drawable area.
	float GetAspect(void);
	
	//! Returns true if the window is open, false otherwise.
	bool	IsOpen(void);

	//! Set a rendering stencil.
	/*! Specify the area of the window you wish to draw to. (x, y) is the coordinate of the bottom left part
	of the rectangle you wish to draw to. Width and height define the rectangle that will be drawable with
	its lower left corner at that point.
	Implemented with glStencil.
	*/
	void	SetRenderMask(float x, float y, float width, float height);

	//! Removes render stencil.
	void	RemoveRenderMask(void);

	//! Get the current drawable area, value depends on the current stencil
	void	GetSize(float &width, float &height);

	//! Clears render zone with the current glClearColor.
	void	Clear(void);
	
	//! Renders entire window, call once per frame.
	void	Render(void);

	//! Check if a key is down.
	bool	key(int key);

	//! Check if a mouse button is pressed.
	bool	mouseButton(int button);

	//! Get the current mouse position.
	const glm::vec2& mousePos(void);

	//! Returns the pointer to the internal GLFW window.
	GLFWwindow* getGLWindow(void);
};

#endif
