#pragma once

#include <string>

struct CellPosition
{
	int x;
	int y;
};

struct Position
{
	float x;
	float y;
	float z;
};

struct Renderable
{
	std::string name;
};
