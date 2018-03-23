
#include "voxGL.hpp"
#include "Particles.class.hpp"

std::vector<float> lifetime;
std::vector<float> speed;

void	init(Particles &particles)
{
	std::vector<float> &pos = particles.GetPhysicalAttributes();
	std::vector<float> &col = particles.GetColorAttributes();

	lifetime.resize(pos.size());
	speed.resize(pos.size());
	
	for (size_t i = 0; i < pos.size(); i+=4)
	{
		pos[i] = 0;
		pos[i + 1] = 0;
		pos[i + 2] = 0;
		pos[i + 3] = 1;
		speed[i] = (1 - (rand() % 100 / 50.0)) * 0.001;
		speed[i + 1] = (rand() % 100 / 100.0) * 0.001;
		speed[i + 2] = (1 - (rand() % 100 / 50.0)) * 0.001;
		
	}

	for (size_t i = 0; i < col.size(); i+=4)
	{
		col[i] = 0.5;
		col[i + 1] = 0.2;
		col[i + 2] = 0;
		col[i + 3] = 0.1;
	}
}

void	update(Particles &particles)
{
        std::vector<float> &pos = particles.GetPhysicalAttributes();
	
	for (size_t i = 0; i < pos.size(); i+=4)
	{
		pos[i] += speed[i];
		pos[i + 1] += speed[i + 1];
		pos[i + 2] += speed[i + 2];

		if (pos[i + 1] <= -1)
			speed[i + 1] *= -1;
		
		speed[i + 1] -= 0.0001;
	}
}

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

	camera.TrackEvents(&window);

	Particles particles(1000);

	glClearColor(0.20, 0.25, 0.29, 1);

	init(particles);
	
	while (window.IsOpen())
	{
		window.Clear();
		camera.Update();
		particles.UsePerspective(camera.Perspective());		

		update(particles);
		particles.Update();
		particles.Render();
		window.Render();

		GLenum err;

		if ((err = glGetError()) != GL_NO_ERROR)
		{
			std::cerr << "OpenGL error: " << err << std::endl;
		}
	}
}
