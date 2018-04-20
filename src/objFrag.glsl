#version 410 core

in ShapeData {		
	vec2 uv;
	vec3 lightMod;
	float dist;
	float fog;
	vec3 fogcol;
} Data;

out vec4 color;

uniform sampler2D tex;

void	main()
{
	float fog = min(pow(Data.dist, 2) / Data.fog, 1);
	vec4 col = texture(tex, Data.uv).rgba * vec4(Data.lightMod, 1);	
	color = col * (1 - fog) + vec4(Data.fogcol * fog, 1);
}