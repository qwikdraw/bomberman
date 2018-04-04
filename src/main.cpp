
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
		pos[i + 3] = 0.1;
		speed[i] = (1 - (rand() % 100 / 50.0)) * 0.01;
		speed[i + 1] = (1 - (rand() % 100 / 50.0)) * 0.01;
		speed[i + 2] = (1 - (rand() % 100 / 50.0)) * 0.01;
		
	}

	for (size_t i = 0; i < col.size(); i+=4)
	{
		col[i] = 0.5;
		col[i + 1] = 0.2;
		col[i + 2] = 0;
		col[i + 3] = 0.5;
	}
}

void	update(Particles &particles)
{
        std::vector<float> &pos = particles.GetPhysicalAttributes();
	std::vector<size_t> &index = particles.GetAttributeIndices();

	for (size_t i = 0; i < pos.size(); i+=4)
	{
		size_t posIndex = index[i / 4] * 4;
		pos[i] += speed[posIndex];
		pos[i + 1] += speed[posIndex + 1];
		pos[i + 2] += speed[posIndex + 2];
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

	Particles particles(100000);
	particles.SetTransform(glm::translate(glm::vec3(0, 0, -10)));

	glClearColor(0.20, 0.25, 0.29, 1);

	init(particles);
	
	while (window.IsOpen())
	{
		window.Clear();
		camera.Update();
		particles.UseExplicitPerspective(camera.ExplicitPerspective());

		update(particles);
		particles.Sort();
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
