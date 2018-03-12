#version 410 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

uniform mat4 transform;
uniform mat4 perspective;

out	ShapeData {
	vec3 color;
} Data;

void	main()
{
	float dot = max( dot( normalize(transform * vec4(normal, 0)),
	normalize(vec4(-1, -2, -3, 0)) ), 0.1 );

	gl_Position = perspective * transform * vec4(vertex, 1);
	Data.color = color * dot;
}