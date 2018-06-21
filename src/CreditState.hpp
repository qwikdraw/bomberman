#pragma once

#include "bomberman.hpp"
#include "IState.hpp"
#include "Sprite2D.hpp"

class	CreditState : public IState
{
	Engine& _engine;
	Window& _window;
	Sprite2D _display;
	
public:
	CreditState(Engine& engine);

	void	Update(double dt);
};
