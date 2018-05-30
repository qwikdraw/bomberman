#pragma once

#include "bomberman.hpp"
#include "IParticle.hpp"
#include "Light.hpp"
#include "Engine.hpp"

//! It is recommended to alias this namespace like so: `namespace c = components;`
namespace components
{

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
		int priority = 0;
	};

	struct Text
	{
		std::string words;
		glm::vec2 botLeft = glm::vec2(-1, -1);
		glm::vec2 topRight = glm::vec2(1, 1);
	};
	
	struct Player
	{
		double speed;
		double bombCooldown;
		int bombPower = 1;
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
		Direction dir = Direction::NONE;
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

	struct Sound
	{
		std::string soundFile;
		float frequency;
		float timePassed = 0;
	};

	struct EngineTag
	{
		Engine& ref;
	};

	enum ActionType{BOMB_ACTION, UP_ACTION, DOWN_ACTION, LEFT_ACTION, RIGHT_ACTION};
	
	struct KeyBind
	{
		ActionType action;
	};
};
