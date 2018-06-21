#include "CreditState.hpp"

CreditState::CreditState(Engine& engine) : _engine(engine),
					   _window(engine.window),
					   _display("assets/textures/credits.png")
{
}

void	CreditState::Update(double)
{
	_display.Render();
	if (_window.MouseClick(0))
		_engine.PopState();
}
