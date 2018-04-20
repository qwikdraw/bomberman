#version 410 core

in ShapeData {		
	vec2 uv;
	vec3 lightMod;
	float dist;
} Data;

out vec4 color;

uniform sampler2D tex;

void	main()
{
	float fog = min(Data.dist / 100, 1);
	vec3 texcol = texture(tex, Data.uv).rgb;
	vec3 fogcol = vec3(0.1, 0, 0);
	vec3 newcol = texcol * (1 - fog) + fogcol * fog;

	color = vec4(newcol, 1) * vec4(Data.lightMod, 1);
}