
#version 410 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec4 position;
layout(location = 2) in vec4 color;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 lookAt;

out vec4 fragColor;

void	main()
{
	float aspect = view[1][1] / view[0][0];
	vec3 centerTransformed = vec3(transform * lookAt * vec4(position.xyz, 1));
	vec3 cameraRight = vec3( view[0][0], view[1][0], view[2][0] );
	vec3 cameraUp = vec3( view[0][1], view[1][1], view[2][1] );
	vec3 vertexPos = centerTransformed +
			cameraRight * vertex.x * position.w * aspect +
			cameraUp * vertex.y * position.w;

	gl_Position = view * vec4(vertexPos, 1);

	fragColor = color;
}
