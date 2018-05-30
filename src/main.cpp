#include "bomberman.hpp"
#include "MenuState.hpp"
#include "ParticleExplosion.hpp"
#include "Effects.hpp"

int	main(void)
{
	Window window(1920, 1080, "bomberman");
	ISoundEngine *sound = createIrrKlangDevice();
	Engine engine(window, *sound);

	Effects::explosion = new ParticleExplosion(1.0f);
	Effects::sparkles = new Sparkles(80, 80);

	engine.PushState(new MenuState(engine));
	while (engine.isRunning)
		engine.Run();

	Effects::CleanUp();
	return 0;
}
