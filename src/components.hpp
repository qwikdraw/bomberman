#pragma once

#include "bomberman.hpp"

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

	struct Transform
	{
		glm::mat4 transform;
	};
	
	struct Model
	{
		std::string name;
		glm::vec2 botLeft = glm::vec2(-1, -1);
		glm::vec2 topRight = glm::vec2(1, 1);
	};

	struct Decay
	{
		float seconds;
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
		std::function<bool(glm::vec3, glm::vec3)> f;
	};
};
