
#include "ObjFiles.hpp"

int	main(int ac, char **av)
{	
	Window window(X_DIM, Y_DIM, NAME);
	Camera camera;

	window.EventListen();

	window.ForwardAndBackKeys('W', 'S');
	window.LeftAndRightKeys('A', 'D');
	window.UpAndDownKeys('Z', 'X');

	camera.TrackEvents(&window);

	ObjFileObject obj("test.obj", "");
	VoxRenderer renderer;

	for (int i = 1; i < ac; i++)
	{

		VoxObject *test = new VoxObject(av[i]);

		test->Load();
		renderer.AttachObject(test);

		test->SetPos(glm::vec3((i - 2) * 20, 0, 0));
	}
	
	obj.SetTransform(glm::mat4(100));
	
	glClearColor(0.3, 0.3, 0.3, 1.0);
	
	while (window.IsOpen())
	{
		window.ClearRenderZone();
		camera.Update();
		obj.UsePerspective(camera.Perspective());
		obj.Render();
		renderer.NewPerspective(camera.Perspective());
		renderer.Render();
		window.UpdateEntireWindow();

		GLenum err;

		if ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cerr << "OpenGL error: " << err << std::endl;
		}
	}
}
