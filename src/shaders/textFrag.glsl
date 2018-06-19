#version 410 core

in vec2 tex_uv;

uniform sampler2D tex;

out vec4 color;

void	main()
{
	color = texture(tex, tex_uv).rgba;
	color.a = pow(color.a, 10);
	color.rgb = pow(color.rgb, vec3(0.1, 0.1, 0.5));
}