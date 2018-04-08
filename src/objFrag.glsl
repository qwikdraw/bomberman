#version 410 core

in ShapeData {
	vec3 normal;
	vec2 uv;
} Data;

out vec3 color;

uniform sampler2D tex;

void	main()
{	
	color = max(dot(Data.normal, vec3(0, 0, 1)), 0.1) * texture(tex, Data.uv).rgb;
}