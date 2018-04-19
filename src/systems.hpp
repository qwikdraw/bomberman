#pragma once

#include "bomberman.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Engine.hpp"
#include "Sprite2D.hpp"
#include "components.hpp"
#include <cstdint>
#include <unordered_map>

#define ASSET_PATH "assets/"
#define MODEL_PREFIX ".model"

#define FACE_UP glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(0, 0, 1))
#define FACE_DOWN glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(0, 0, 1))
#define FACE_LEFT glm::rotate(glm::mat4(1), glm::radians(180.0f), glm::vec3(0, 0, 1))
#define FACE_RIGHT glm::mat4(1)

//! It is recommended to alias this namespace like so: `namespace s = systems;

namespace systems
{
	//! requires: Model, Position
	void	RenderModels(entt::DefaultRegistry&, entt::ResourceCache<Model>&, Window&, Camera&);

	//! requires: Decay
	void	Decay(entt::DefaultRegistry&, double dt);

	//! requires: Button
	void	Buttons(entt::DefaultRegistry&, entt::ResourceCache<Sprite2D>&, Window&, double dt);


	//! requires: Position, Velocity
	void	Velocity(entt::DefaultRegistry&);

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

	//! requires: Player, Position, Velocity
	void	Player(entt::DefaultRegistry&, Window&, Collisions&, double dt);
};
