#include "voxGL.hpp"

static const GLfloat vertices[6] = {
	-1.0f, -1.0f,
	1.0f, -1.0f,
	1.0f, 1.0f
};

int	main(void)
{
	Window window(1024, 1024, "Clear Stencil Test");
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
	while (window.IsOpen())
	{
		window.RemoveRenderMask();
		window.Clear();

		if (window.key(GLFW_KEY_SPACE)) {
			window.SetRenderMask(0,0,0.1,0.2);
		}
		if (window.key(GLFW_KEY_1)) {
			std::cout << "Aspect Ratio: " << window.GetAspect() << std::endl;
		}
		if (window.key(GLFW_KEY_2)) {
			std::cout << "MousePos().x: " << window.mousePos().x << std::endl;
		}
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window.Render();
		GLenum err;
		if ((err = glGetError()) != GL_NO_ERROR)
			std::cerr << err << std::endl;
		if (window.key(GLFW_KEY_ESCAPE)) {
			glfwTerminate();
			return (0);
		}
	}
}
