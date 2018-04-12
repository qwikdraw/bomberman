#include "voxGL.hpp"

#include "TestState.hpp"

TestState::TestState(void) :
_camera(Camera()),
_animation(AnimatedObject("src/animationFile"))
{
	_camera.Move(glm::vec3(-10, 0, 3));
	for (int i = 0; i < 10; ++i)
		_lights.push_back(new Light(glm::vec3(0, 0, 4), glm::vec3(1, 1, 1), 2));
	if (glGetError() != GL_NO_ERROR)
		std::cerr << "FAIL\n";
}

TestState::~TestState(void)
{
	for (auto l: _lights) {
		delete l;
	}
}

void TestState::Update(Engine* engine, Window& window, double)
{
	if (window.Key(GLFW_KEY_SPACE)) {
		window.Clear();
		window.SetRenderMask(0.25f,0.25f,0.5f,0.5f);
	} else {
		window.RemoveRenderMask();
	}
	if (window.Key(GLFW_KEY_ESCAPE))
	{
		engine->isRunning = false;
	}
	if (window.Key(GLFW_KEY_1))
	{
		engine->ChangeState(new TestState());
	}
}

void TestState::Draw(Engine*, Window& window, double)
{
	window.Clear();
	_camera.SetAspect(window.GetAspect());
	_animation.UsePerspective(_camera.Perspective());
	_animation.Render();
}
