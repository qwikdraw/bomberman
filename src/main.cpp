#include "bomberman.hpp"
#include "MenuState.hpp"
#include "ParticleExplosion.hpp"
#include "Effects.hpp"

int	main(void)
{
	Window window(1024, 1024, "bomberman");
	Engine engine(window);

	Effects::explosion = new ParticleExplosion(1.0f);
	
	engine.PushState(new MenuState(engine));
	while (engine.isRunning)
	{
		engine.Run();
	}

	Effects::CleanUp();
	
	return 0;
}
