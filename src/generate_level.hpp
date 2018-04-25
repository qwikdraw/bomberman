#pragma once

#include "bomberman.hpp"
#include "components.hpp"
#include "ParticleExplosion.hpp"

namespace c = components;

void	generate_level(entt::DefaultRegistry &r, int w, int h, ParticleExplosion*);
