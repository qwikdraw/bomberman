#include "TestState.hpp"

TestState::TestState(void) {
	static const GLfloat vertices[6] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		1.0f, 1.0f
	};
	ShadingProgram program(
		"src/shaders/vertex_2d_simple.glsl",
		"",
		"src/shaders/frag_simple.glsl"
	);
	program.Use();
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
}

TestState::~TestState(void) {}

void TestState::Update(Engine*, Window& window, double) {
		if (window.key(GLFW_KEY_SPACE)) {
			window.Clear();
			window.SetRenderMask(0,0,0.1,0.2);
		} else {
			window.RemoveRenderMask();
		}
		if (window.key(GLFW_KEY_1)) {
			std::cout << "Aspect Ratio: " << window.GetAspect() << std::endl;
		}
		if (window.key(GLFW_KEY_2)) {
			std::cout << "MousePos().x: " << window.mousePos().x << std::endl;
		}
		if (window.key(GLFW_KEY_ESCAPE)) {
			glfwTerminate();
			exit(1);
		}
}

void TestState::Draw(Engine*, Window& window, double) {
		window.Clear();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window.Render();
}
