#pragma once

#include "bomberman.hpp"
#include "components.hpp"
#include "ParticleExplosion.hpp"
#include "Effects.hpp"
#include "scripts.hpp"
#include "Engine.hpp"

namespace c = components;

void	build_level(entt::DefaultRegistry &r, Engine& engine, std::string level,
		i::ISound **_music);
void	add_wall(entt::DefaultRegistry& r, uint32_t e);
void	remove_wall(entt::DefaultRegistry& r, uint32_t e);
