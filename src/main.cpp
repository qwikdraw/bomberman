#include "voxGL.hpp"
#include "AnimatedObject.hpp"
#include "Camera.hpp"
#include "Light.hpp"

int	main(void)
{
	Window window(500, 500, "bomberman");
	Camera camera;

        if (glGetError() !=GL_NO_ERROR)
                std::cerr << "FAIL\n";
	camera.Move(glm::vec3(-10, 0, 3));
//	camera.Rotate(glm::vec3(1, 0, 0), -90);

	AnimatedObject animation("src/animationFile");
	std::vector<Light*> lights;

	for (int i = 0;  i < 100; ++i)
		lights.push_back(new Light(glm::vec3(0, i, 4), glm::vec3(1, 1, 1), 2));

	std::cout << Light::positions.size() << std::endl;
	
	while (window.IsOpen())
	{
		window.RemoveRenderMask();
		window.Clear();

		if (window.key(GLFW_KEY_SPACE)) {
			window.SetRenderMask(0,0,0.1,1);
		}
		if (window.key(GLFW_KEY_1)) {
			std::cout << "Aspect Ratio: " << window.GetAspect() << std::endl;
		}
		if (window.key(GLFW_KEY_2)) {
			std::cout << "MousePos().x: " << window.mousePos().x << std::endl;
		}
		camera.SetAspect(window.GetAspect());
		animation.UsePerspective(camera.Perspective());
		animation.Render();
		
		window.Render();
		
		GLenum err;
		if ((err = glGetError()) != GL_NO_ERROR)
			std::cerr << err << std::endl;
		
		if (window.key(GLFW_KEY_ESCAPE))
			window.SetClosed();
	}
}
