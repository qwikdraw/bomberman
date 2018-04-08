#version 410 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 transform;
uniform mat4 perspective;

out	ShapeData {
	vec3 normal;
	vec2 uv;
} Data;

void	main()
{
	Data.normal = vec3(perspective * transform * vec4(normal, 0));
	Data.uv = uv;
	gl_Position = perspective * transform * vec4(vertex, 1);
}