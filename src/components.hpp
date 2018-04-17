#pragma once

#include "bomberman.hpp"

namespace Part
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
	};

	struct Decay
	{
		float seconds;
	};

	struct ScreenArea
	{
		glm::vec2 botLeft;
		glm::vec2 topRight;
	};
	
	struct ClickCallback
	{
		std::function<void()> f;
		float cooldown = 0;
		float cooldownTimer = 0;
	};

	struct Button
	{
		std::string imageBefore;
		std::string imageAfter;
	};
};
