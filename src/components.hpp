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
		glm::vec2 botLeft = glm::vec2(-1, -1);
		glm::vec2 topRight = glm::vec2(1, 1);
	};

	enum class effect{EXPLOAD, VANISH};
	
	struct TimedEffect
	{
		float timeLeft = 0.0f;
		effect effectType = effect::VANISH;
	};

	struct Button
	{
		std::string imageBefore;
		std::string imageAfter;
		std::function<void()> f;
		glm::vec2 botLeft;
		glm::vec2 topRight;
		float cooldown = 0;
		float cooldownTimer = 0;
	};

	struct Player
	{
		double speed;
		double bombCooldown;
		double bombCooldownTimer = 0;
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
	};

	struct Lighting
	{
		glm::vec3 color;
		float falloff;
		glm::vec3 displacement = glm::vec3(0, 0, 0);
	};

	enum class Direction{NONE, UP, RIGHT, DOWN, LEFT};

	struct Explosion
	{
		int spread = 0;
		Direction dir = Direction::NONE;
	};
};
