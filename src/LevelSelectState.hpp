#pragma once

#include "bomberman.hpp"
#include "Light.hpp"
#include "IState.hpp"
#include "Model.hpp"
#include "Sprite2D.hpp"
#include <entt/entt.hpp>

//! Level select state class. Implements IState
/*!
 * Allows access to any unlocked level (game state). Shows locked levels.
*/

class	LevelSelectState : public IState
{
	Engine& _engine;
	Window& _window;
	entt::DefaultRegistry _registry;
	entt::ResourceCache<Sprite2D> _imageCache;

public:
	LevelSelectState(Engine& engine);

	~LevelSelectState(void);

	//! Updates buttons, images, and texts systems per frame.
	void	Update(double dt);	
};
