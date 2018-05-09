#pragma once

#include "bomberman.hpp"
#include "IParticle.hpp"
#include "Light.hpp"

//! It is recommended to alias this namespace like so: `namespace c = components;`
namespace components
{

	struct CellPosition
	{
		int x;
		int y;
	};

	struct Position
	{
		glm::vec3 pos;
	};

	struct Model
	{
		std::string name;
		glm::mat4 transform;
		float time = 0;
		glm::vec2 botLeft = glm::vec2(-1, -1);
		glm::vec2 topRight = glm::vec2(1, 1);
	};

	struct TimedEffect
	{
		float timeLeft;
		std::function<void(entt::DefaultRegistry&, uint32_t)> effect;
	};

	struct Button
	{
                std::function<void(entt::DefaultRegistry&, uint32_t)> onClick;
		glm::vec2 botLeft = glm::vec2(-1, -1);
		glm::vec2 topRight = glm::vec2(1, 1);
	};

	struct Image
	{		
		std::string name;
		glm::vec2 botLeft = glm::vec2(-1, -1);
		glm::vec2 topRight = glm::vec2(1, 1);
	};
	
	struct Player
	{
		double speed;
		double bombCooldown;
		int bombPower = 1;
		double bombCooldownTimer = 0;

		~Player(){std::cout << "test" << std::endl;}
	};

	struct Velocity
	{
		glm::vec3 v = glm::vec3(0, 0, 0);
	};

	struct Collide
	{
		int height = 10;
	};

	struct Particles
	{
		IParticle *particle;
		float duration;
	};

	struct Lighting
	{
		glm::vec3 color;
		float falloff;
		glm::vec3 displacement = glm::vec3(0, 0, 0);
		float falloffDelta = 0.0f;
	};

	enum class Direction{NONE, UP, RIGHT, DOWN, LEFT};

	struct Explosion
	{
		int spread = 0;
	};

	enum class AI_type{RAND, HORZ, VERT};

	struct AI
	{
		double speed;
		double moveCooldown;
		AI_type type;
		double moveCooldownTimer = 0.0;
		Direction dir = Direction::NONE;
	};

	struct Dangerous
	{
		int dangerLevel = 1;
	};

	struct Vulnerable
	{
		std::function<void(entt::DefaultRegistry&, uint32_t)> onDeath;
		int dangerResist = 0;
	};

	struct Powerup
	{
		std::function<void(entt::DefaultRegistry&, uint32_t)> effect;
	};
};
