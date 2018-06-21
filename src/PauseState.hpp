#pragma once

#include "bomberman.hpp"
#include "Light.hpp"
#include "IState.hpp"
#include "Model.hpp"
#include "Sprite2D.hpp"
#include <entt/entt.hpp>

//! Pause state class. Implements IState
/*! 
 * Pauses the game state. Allows access to the main menu, settings, back to the game, or quitting.
*/

class	PauseState : public IState
{
	Engine& _engine;
	Window& _window;
	entt::DefaultRegistry _registry;
	entt::ResourceCache<Sprite2D> _imageCache;

public:
	PauseState(Engine& engine);

	~PauseState(void);

	//! Updates buttons, images, and texts systems per frame.
	void	Update(double dt);
};
