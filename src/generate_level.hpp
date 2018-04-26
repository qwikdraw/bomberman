#pragma once

#include "bomberman.hpp"
#include "components.hpp"
#include "ParticleExplosion.hpp"
#include "Effects.hpp"
#include "callbacks.hpp"

namespace c = components;

void	generate_level(entt::DefaultRegistry &r, int w, int h);
