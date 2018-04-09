#version 410 core

in ShapeData {
	float dot;
	vec2 uv;
} Data;

out vec3 color;

uniform sampler2D tex;

void	main()
{	
	color = max(Data.dot, 0.2) * texture(tex, Data.uv).rgb;
}