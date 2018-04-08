
#include "voxGL.hpp"
#include "AnimatedObject.hpp"

int	main(void)
{
	
	Window window(X_DIM, Y_DIM, NAME);
	Camera camera;

        if (glGetError() !=GL_NO_ERROR)
                std::cerr << "FAIL\n";


//	window.EventListen();

	glClearColor(0.20, 0.25, 0.29, 1);

	camera.Move(glm::vec3(-10, 0, 3));
	camera.Rotate(glm::vec3(1, 0, 0), -90);

//	ObjFileObject p("src/bomb.obj", "twaltonTestEnvironment/Tulips.bmp");
	
	AnimatedObject animation("src/animationFile");
	
	std::cout << "animation loaded" << std::endl;
	
	while (window.IsOpen())
	{
		window.Clear();

		animation.UsePerspective(camera.Perspective());
		animation.Render();
		
		window.Render();

		GLenum err;

		if ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cerr << "OpenGL error: " << err << std::endl;
		}
	}
}
