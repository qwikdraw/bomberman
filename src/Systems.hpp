#pragma once

#include "bomberman.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "components.hpp"

#define ASSET_PATH "assets/"
#define MODEL_PREFIX ".model"

namespace Systems
{
	//! requires: Model, Position
	void	RenderModels(entt::DefaultRegistry&, Camera&);
};
