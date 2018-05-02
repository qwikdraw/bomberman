#version 410 core

in vec2 tex_uv;

uniform sampler2D tex;

out vec4 color;

void	main()
{
	color = texture(tex, tex_uv).rgba;
}