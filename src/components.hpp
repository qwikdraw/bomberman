#pragma once

#include "bomberman.hpp"
#include "IParticle.hpp"
#include "Light.hpp"
#include "Engine.hpp"

//! It is recommended to alias this namespace like so: `namespace c = components;`
namespace components
{

	//! Entity position
	struct Position
	{
		glm::vec3 pos;
	};

	/*! Abstract 3d model component.
	* includes texture and animation,
	* only the name of the model is stored here and a cache is used.
	*/
	struct Model
	{
		std::string name;
		glm::mat4 transform;
		float time = 0;
		glm::vec2 botLeft = glm::vec2(-1, -1);
		glm::vec2 topRight = glm::vec2(1, 1);
	};

	//! Something that will happen have after a certian ammount of time.
	struct TimedEffect
	{
		float timeLeft;
		std::function<void(entt::DefaultRegistry&, uint32_t)> effect;
	};

	//! Game UI button
	struct Button
	{
                std::function<void(entt::DefaultRegistry&, uint32_t)> onClick;
		glm::vec2 botLeft = glm::vec2(-1, -1);
		glm::vec2 topRight = glm::vec2(1, 1);
	};

	//! Generic image
	struct Image
	{		
		std::string name;
		glm::vec2 botLeft = glm::vec2(-1, -1);
		glm::vec2 topRight = glm::vec2(1, 1);
		int priority = 0;
	};

	//! Generic text
	struct Text
	{
		std::string words;
		glm::vec2 botLeft = glm::vec2(-1, -1);
		glm::vec2 topRight = glm::vec2(1, 1);
	};

	//! Entity Player data
	struct Player
	{
		double speed;
		double bombCooldown;
		int bombPower = 1;
		double bombCooldownTimer = 0;
	};

	//! Entity velocity
	struct Velocity
	{
		glm::vec3 v = glm::vec3(0, 0, 0);
	};

	//! Entity collisions
	struct Collide
	{
		int height = 10;
	};

	//! Particle Effect
	struct Particles
	{
		IParticle *particle;
		float duration;
	};

	//! Entity light emission
	struct Lighting
	{
		glm::vec3 color;
		float falloff;
		glm::vec3 displacement = glm::vec3(0, 0, 0);
		float falloffDelta = 0.0f;
	};

	enum class Direction{NONE, UP, RIGHT, DOWN, LEFT};

	//! Entity exposion
	struct Explosion
	{
		int spread = 0;
	};

	enum class AI_Type{HORZ, VERT, MAZE};

	//! Entity AI
	struct AI
	{
		AI_Type type = AI_Type::HORZ;
		double speed = 1.5;
		Direction dir = Direction::NONE;
		double moveCooldown = 0.5;
		double moveCooldownTimer = 0.0;
	};

	//! Represents dangerous entities such as fire. Effects entities with vulnerable
	struct Dangerous
	{
		int dangerLevel = 1;
	};

	//! Entity is effected by danger
	struct Vulnerable
	{
		std::function<void(entt::DefaultRegistry&, uint32_t)> onDeath;
		int dangerResist = 0;
	};

	//! Powerup
	struct Powerup
	{
		std::function<void(entt::DefaultRegistry&, uint32_t)> effect;
	};

	//! Sound
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
