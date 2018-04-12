#include "voxGL.hpp"
#include "TestState.hpp"

int	main(void)
{
	Window window(1024, 1024, "bomberman");
	Engine engine(window);
	engine.PushState(new TestState());
	while (engine.isRunning)
	{
		engine.Run();
	}
	return 0;
}
