#version 410 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 lookAt;

out	ShapeData {
	float dot;
	vec2 uv;
} Data;

void	main()
{
	vec3 actualNormal = normalize(vec3(lookAt * transform * vec4(normal, 0)));

	vec3 actualVertex = vec3(lookAt * transform * vec4(vertex, 1));
	vec3 viewPoint = vec3(lookAt * transform * vec4(0, 0, 0, 0));

	Data.dot = dot(actualNormal, -normalize(actualVertex - viewPoint));

	Data.uv = uv;
	gl_Position = projection * lookAt * transform * vec4(vertex, 1);
}