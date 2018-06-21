#pragma once

#include "bomberman.hpp"
#include "Light.hpp"
#include "IState.hpp"
#include "Model.hpp"
#include "Sprite2D.hpp"
#include <entt/entt.hpp>

//! Setting state class. Implements IState
/*
 * Allows player to change key bindings, resolution, turn sound off/on.
*/

class	SettingState : public IState
{
	Engine& _engine;
	Window& _window;
	entt::DefaultRegistry _registry;
	entt::ResourceCache<Sprite2D> _imageCache;

public:
	SettingState(Engine& engine);

	~SettingState(void);

	//! Updates bind checks, buttons, images, texts per frame.
	void	Update(double dt);
};
