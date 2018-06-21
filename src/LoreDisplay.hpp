#pragma once

#include "bomberman.hpp"
#include "Window.hpp"
#include "Sprite2D.hpp"

class	LoreDisplay
{
	Sprite2D _pannel;
	bool _shouldDisplay;
	Window& _window;
public:

	LoreDisplay(std::string level, Window& window);

	bool	ShouldDisplay(void);
	void	Render(void);
};
