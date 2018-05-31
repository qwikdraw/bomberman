#pragma once

#include "bomberman.hpp"
#include "Light.hpp"
#include "IState.hpp"
#include "Model.hpp"
#include "Sprite2D.hpp"
#include <entt/entt.hpp>

class	SettingState : public IState
{
	Engine& _engine;
	Window& _window;
	entt::DefaultRegistry _registry;
	entt::ResourceCache<Sprite2D> _imageCache;

public:
	SettingState(Engine& engine);
	~SettingState(void);
	void	Update(double dt);
};
