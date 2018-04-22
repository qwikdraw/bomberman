#pragma once

#include "bomberman.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Engine.hpp"
#include "Sprite2D.hpp"
#include "components.hpp"
#include <cstdint>
#include <unordered_map>
#include "ParticleExplosion.hpp"

#define ASSET_PATH "assets/"
#define MODEL_PREFIX ".model"

#define FACE_UP glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(0, 0, 1))
#define FACE_DOWN glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(0, 0, 1))
#define FACE_LEFT glm::rotate(glm::mat4(1), glm::radians(180.0f), glm::vec3(0, 0, 1))
#define FACE_RIGHT glm::mat4(1)

//! It is recommended to alias this namespace like so: `namespace s = systems;

namespace systems
{
	//! requires: Model, Position [Lighting]
	void	RenderModels(entt::DefaultRegistry&, entt::ResourceCache<Model>&, Window&, Camera&);

	//! requires: TimedEffect
	void	TimedEffect(entt::DefaultRegistry&, double dt);

	//! requires: Button
	void	Buttons(entt::DefaultRegistry&, entt::ResourceCache<Sprite2D>&, Window&, double dt);

	//! requires: Position, Collide
	class  Collisions
	{
		std::unordered_map<uint64_t, uint32_t> _cells;
	public:
		Collisions(void);
		bool isEmpty(float x, float y) const;
		uint32_t get(float x, float y);
		void operator()(entt::DefaultRegistry&);
	};

	//! requires: Lighting; Applies falloff delta
	void	Lighting(entt::DefaultRegistry&, double dt);

	//! requires: Position, Velocity [Collide]
	void	Velocity(entt::DefaultRegistry&, Collisions&, double dt);

	//! requires: Player, Position, Velocity, Model
	void	Player(entt::DefaultRegistry&, Window&, Engine::KeyBind, Camera&, double dt);

	//! requires: Particles, Position, TimedEffect
	void	RenderParticles(entt::DefaultRegistry&, Camera&);	


	//! requires: Explosion
	void	Explosion(entt::DefaultRegistry&, Collisions&, ParticleExplosion*);
};
