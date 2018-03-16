#version 410 core

in ShapeData {
	vec3 normal;
	vec2 uv;
} Data;

out vec3 color;

uniform sampler2D tex;

void	main()
{
	color = texture(tex, Data.uv).rgb;
}