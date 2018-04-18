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

	struct Model
	{
		std::string name;
		glm::mat4 transform;
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
};
