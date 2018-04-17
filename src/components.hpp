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

	struct Clickable
	{
		glm::vec2 botLeft;
		glm::vec2 topRight;
		std::function<void()> f;
	};
};
