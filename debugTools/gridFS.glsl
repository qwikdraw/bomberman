
#version 410 core

in float transparency;

out vec4 color;

void	main()
{
	color = vec4(0.8, 0.3, 0.3, transparency);
}