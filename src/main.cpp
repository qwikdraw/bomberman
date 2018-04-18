#include "bomberman.hpp"
#include "MenuState.hpp"

int	main(void)
{
	Window window(1024, 1024, "bomberman");
	Engine engine(window);
	engine.PushState(new MenuState(engine));
	while (engine.isRunning)
	{
		engine.Run();
	}
	return 0;
}
