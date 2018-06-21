#include "LoreDisplay.hpp"

LoreDisplay::LoreDisplay(std::string level, Window& window) :
_pannel("assets/textures/lore_pannel" + level + ".png"),
_shouldDisplay(true),
_window(window)
{
}

bool	LoreDisplay::ShouldDisplay(void)
{
	return _shouldDisplay;
}

void	LoreDisplay::Render(void)
{
	_pannel.Render();
	if (_window.MouseClick(0))
		_shouldDisplay = false;
}
