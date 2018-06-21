#pragma once

#include "bomberman.hpp"
#include "Engine.hpp"
#include "IState.hpp"
#include "systems.hpp"
#include "components.hpp"

//! Death state class. Implements IState
/*!
 * The game over/credits screen. Appears when player dies
*/
class	DeathState : public IState
{
	Engine& _engine;
	Window& _window;
	entt::DefaultRegistry _registry;
	entt::ResourceCache<Sprite2D> _imageCache;

public:
	DeathState(Engine& engine, std::string level);
	~DeathState(void);
	void	Update(double dt);
};
