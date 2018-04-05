
#include "voxGL.hpp"

int	main(void)
{
	
	Window window(X_DIM, Y_DIM, NAME);
	Camera camera;

        if (glGetError() !=GL_NO_ERROR)
                std::cerr << "FAIL\n";


	window.EventListen();

	window.ForwardAndBackKeys('W', 'S');
	window.LeftAndRightKeys('A', 'D');
	window.UpAndDownKeys('Z', 'X');

	glClearColor(0.20, 0.25, 0.29, 1);

	camera.Move(glm::vec3(-20, 0, 0));
	camera.Rotate(glm::vec3(0, 0, 1), 45);
	
	VoxObject o("src/voxelModels/bomb.voxobj");	
	VoxRenderer vr;

	o.Load();
	vr.AttachObject(&o);	
	
	while (window.IsOpen())
	{
		window.Clear();

		vr.NewPerspective(camera.Perspective());
		vr.Render();
		
		window.Render();

		GLenum err;

		if ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cerr << "OpenGL error: " << err << std::endl;
		}
	}
}
