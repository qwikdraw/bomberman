#version 410 core

in ShapeData {
	vec2 uv;
	vec3 lightMod;
} Data;

out vec4 color;

uniform sampler2D tex;

void	main()
{	
	color = texture(tex, Data.uv).rgba * vec4(Data.lightMod, 1);
}