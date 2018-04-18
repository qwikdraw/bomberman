#pragma once

#include "bomberman.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Engine.hpp"
#include "Sprite2D.hpp"
#include "components.hpp"

#define ASSET_PATH "assets/"
#define MODEL_PREFIX ".model"

#define FACE_UP
#define FACE_DOWN
#define FACE_LEFT
#define FACE_RIGHT

//! It is recommended to alias this namespace like so: `namespace s = systems;

namespace systems
{
	//! requires: Model, Position
	void	RenderModels(entt::DefaultRegistry&, entt::ResourceCache<Model>&, Window&, Camera&);

	//! requires: Decay
	void	Decay(entt::DefaultRegistry&, double dt);

	//! requires: Button
	void	Buttons(entt::DefaultRegistry&, entt::ResourceCache<Sprite2D>&, Window&, double dt);

	//! requires: Player, Position, Velocity
	void	PlayerEvents(entt::DefaultRegistry&, Window&, double dt);

	//! requires: Position, Velocity
	void	ApplyMovements(entt::DefaultRegistry&);
};
