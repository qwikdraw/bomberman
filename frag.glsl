#version 410 core

in ShapeData {
	vec3 color;
} Data;

out vec3 color;

void	main()
{
	color = Data.color;
}