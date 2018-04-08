#include "voxGL.hpp"
#include "AnimatedObject.hpp"
#include "Camera.hpp"

int	main(void)
{
	Window window(500, 500, "bomberman");
	Camera camera;

        if (glGetError() !=GL_NO_ERROR)
                std::cerr << "FAIL\n";


	glClearColor(0.20, 0.25, 0.29, 1);

	camera.Move(glm::vec3(-10, 0, 3));
	camera.Rotate(glm::vec3(1, 0, 0), -90);

	AnimatedObject animation("src/animationFile");
	
	std::cout << "animation loaded" << std::endl;
	

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
		camera.SetAspect(window.GetAspect());
		animation.UseExplicitPerspective(camera.ExplicitPerspective());
		animation.Render();
		
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
