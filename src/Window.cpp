#include "voxGL.hpp"
#include <stdexcept>

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
	_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (!_window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to initialize window");
	}
	glfwSetWindowUserPointer(_window, this);
	glfwSetWindowSizeCallback(_window, WindowResizeCallback);
	glfwSetWindowPosCallback(_window, WindowMoveCallback);
	glfwSetKeyCallback(_window, KeyCallback);
	glfwMakeContextCurrent(_window);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);
	WindowHints();
}

void	Window::WindowHints(void)
{
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DEPTH_BITS, 32);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);
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
	_screenCornerX = 0;
	_screenCornerY = 0;
	_width = 1;
	_height = 1;

	float width, height;
	GetSize(width, height);
	glViewport(0, 0, width, height);
	glScissor(0, 0, width, height);
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
	Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

	window->RefreshStencil();
}

void	Window::WindowMoveCallback(GLFWwindow *glfwWindow, int, int)
{
	Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

	window->RefreshStencil();
}

void	Window::ErrorCallback(int, const char *description)
{
	std::cerr << description << std::endl;
}

GLFWwindow* Window::getGLWindow(void)
{
	return _window;
}

void	KeyCallback(GLFWwindow *glfwWindow, int key, int, int action, int)
{
	Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
	if (action == GLFW_PRESS) {
		window->_keys[key] = true;
	}
	else if (action == GLFW_RELEASE)
		window->_keys[key] = false;
}
