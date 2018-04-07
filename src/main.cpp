#include "voxGL.hpp"
#include "Engine.hpp"
#include "TestState.hpp"

int	main(void)
{
	Engine engine("Test");
	engine.PushState(new TestState());
	while (1)
	{
		engine.Update();
		engine.Draw();
	}
}
