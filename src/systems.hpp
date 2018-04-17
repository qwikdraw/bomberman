#pragma once

#include "bomberman.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Engine.hpp"
#include "Sprite2D.hpp"
#include "components.hpp"

#define ASSET_PATH "assets/"
#define MODEL_PREFIX ".model"

//! It is recommended to alias this namespace like so: `namespace s = systems;`
namespace systems
{
	//! requires: Model, Position
	void	RenderModels(entt::DefaultRegistry&, entt::ResourceCache<Model>&, Window&, Camera&);

	//! requires: Decay
	void	Decay(entt::DefaultRegistry&, double dt);

	void	Buttons(entt::DefaultRegistry&, entt::ResourceCache<Sprite2D>&, Window&, double dt);
};
