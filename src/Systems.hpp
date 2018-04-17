#pragma once

#include "bomberman.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Engine.hpp"
#include "ScreenImage.hpp"
#include "components.hpp"

#define ASSET_PATH "assets/"
#define MODEL_PREFIX ".model"

namespace Systems
{
	//! requires: Model, Position
	void	RenderModels(entt::DefaultRegistry&, Camera&);

	//! requires: Decay
	void	Decay(entt::DefaultRegistry&, float dt);

	//! requires: ScreenArea, ClickCallback
	void	Clickable(entt::DefaultRegistry&, Window &, float dt);

	//! requires: ScreenArea, ClickCallback, Button
	void	RenderButtons(entt::DefaultRegistry&, Window&);
};
