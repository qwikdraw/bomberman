#include "voxGL.hpp"
#include <stdexcept>

Window::Window(void){}

Window::Window(int width, int height, std::string name) :
						 _screenCornerX(0),
						 _screenCornerY(0),
						 _width(1),
						 _height(1)
{
	GLuint vertex_array_id;

	if (glfwInit() == GLFW_FALSE)
		throw std::runtime_error("Failed to initialize GLFW");
	WindowHints();
	glfwSetErrorCallback(ErrorCallback);
	if (!(_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL)))
	{
		glfwTerminate();
		throw std::runtime_error("Failed to initialize window");
	}
	glfwSetWindowUserPointer(_window, this);
	glfwSetWindowSizeCallback(_window, WindowResizeCallback);
	glfwSetWindowPosCallback(_window, WindowMoveCallback);
	glfwMakeContextCurrent(_window);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);
}

void	Window::WindowHints(void)
{
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_DEPTH_BITS, 32);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void	Window::GetSize(float &width, float &height)
{
	int iwidth, iheight;

	glfwGetFramebufferSize(_window, &iwidth, &iheight);
	
	width = static_cast<float>(iwidth);
	height = static_cast<float>(iheight);
}

bool	Window::IsOpen(void)
{
	return !glfwWindowShouldClose(_window);
}

void	Window::GetDrawableSize(float &width, float &height)
{
	float actualWidth, actualHeight;

	GetSize(actualWidth, actualHeight);

	width = _width * actualWidth;
	height = _height * actualHeight;
}

void	Window::SetStencil(float x, float y, float width, float height)
{
	float windowWidth, windowHeight;

	_width = width;
	_height = height;
	_screenCornerX = x;
	_screenCornerY = y;
	
	GetSize(windowWidth, windowHeight);

	glEnable(GL_SCISSOR_TEST);
	glViewport(windowWidth * x,
		   windowHeight * y,
		   windowWidth * width,		
		   windowHeight * height);
	
	glScissor(windowWidth * x,
		  windowHeight * y,
		  windowWidth * width,
		  windowHeight * height);
}

void	Window::ClearStencil(void)
{
	float windowWidth, windowHeight;

	GetSize(windowWidth, windowHeight);

	_screenCornerX = 0;
	_screenCornerY = 0;
	_width = windowWidth;
	_height = windowHeight;

	glViewport(0, 0, windowWidth, windowHeight);
	glScissor(0, 0, windowWidth, windowHeight);
	glDisable(GL_SCISSOR_TEST);
}


void	Window::Render(void)
{
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void	Window::Clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void	Window::RefreshStencil(void)
{
	SetStencil(_screenCornerX, _screenCornerY, _width, _height);
}

void	Window::WindowResizeCallback(GLFWwindow *glfwWindow, int, int)
{
	Window *window = reinterpret_cast<Window*>( glfwGetWindowUserPointer(glfwWindow) );

	window->RefreshStencil();
}

void	Window::WindowMoveCallback(GLFWwindow *glfwWindow, int, int)
{
	Window *window = reinterpret_cast<Window*>( glfwGetWindowUserPointer(glfwWindow) );

	window->RefreshStencil();
}

void	Window::EventListen(void)
{
	glfwSetKeyCallback(_window, KeyCallback);
}

void	Window::KeyCallback(GLFWwindow *glfwWindow, int key, int, int action, int)
{
	Window *window = reinterpret_cast<Window*>( glfwGetWindowUserPointer(glfwWindow) );

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(glfwWindow, GL_TRUE);

	if (action == GLFW_PRESS)
	{
		window->KeyOn(key) = true;
	}
	else if (action == GLFW_RELEASE)
		window->KeyOn(key) = false;
}

void	Window::ErrorCallback(int, const char *description)
{
	std::cerr << description << std::endl;
}

bool	&Window::KeyOn(int key)
{
	return _keyHeld[key];
}

void	Window::ForwardAndBackKeys(int forward, int backward)
{
	_forward = forward;
	_backward = backward;
}

void	Window::LeftAndRightKeys(int left, int right)
{
	_left = left;
	_right = right;
}

void	Window::UpAndDownKeys(int up, int down)
{
	_up = up;
	_down = down;	
}

bool	Window::IsForward(void)
{
	if (_keyHeld[_forward])
		return true;
	return false;
}

bool	Window::IsBackward(void)
{
	if (_keyHeld[_backward])
		return true;
	return false;
}

bool	Window::IsLeft(void)
{
	if (_keyHeld[_left])
		return true;
	return false;
}

bool	Window::IsRight(void)
{
	if (_keyHeld[_right])
		return true;
	return false;
}

bool	Window::IsUp(void)
{
	if (_keyHeld[_up])
		return true;
	return false;
}

bool	Window::IsDown(void)
{
	if (_keyHeld[_down])
		return true;
	return false;
}
