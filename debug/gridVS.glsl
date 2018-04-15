
#version 410 core

layout(location = 0) in vec3 vertex;

uniform mat4 perspective;

out float transparency;

void	main()
{
	vec4 pos = perspective * vec4(vertex, 1);
	transparency = 1;
	gl_Position = pos;
}