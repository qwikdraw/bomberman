
#include "LowLevelDraw.hpp"
#include "TestMap.class.hpp"

int	main(int ac, char **av)
{	
	Window window(X_DIM, Y_DIM, NAME);
	Camera camera;

	window.EventListen();

	window.ForwardAndBackKeys('W', 'S');
	window.LeftAndRightKeys('A', 'D');
	window.UpAndDownKeys('Z', 'X');

	camera.TrackEvents(&window);

	TestMap map;

	ScreenImage im("Tulips.bmp");

	glClearColor(0.3, 0.3, 0.3, 1.0);
	
	while (window.IsOpen())
	{
		window.ClearRenderZone();
		camera.Update();
		map.UsePerspective(camera.Perspective());
		im.Render();
		map.Render();
		window.UpdateEntireWindow();

		GLenum err;

		if ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cerr << "OpenGL error: " << err << std::endl;
		}
	}
}
