
#version 410 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec4 position;
layout(location = 2) in vec4 color;

uniform mat4 transform;
uniform mat4 perspective;

out vec4 fragColor;

float rand(vec2 co)
{
    return 1 - fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

mat4	randomRotationMatrix(vec2 co)
{
	return rotationMatrix(vec3(rand(co), rand(co * 2), rand(co * 3)), rand(co * 4) * 6.5);
}

void	main()
{
	vec3 rotatedVertex = vertex;//vec3(randomRotationMatrix(position.xy) * vec4(vertex, 1));
	
	gl_Position = perspective * transform * vec4(rotatedVertex * position.w + position.xyz, 1);

	fragColor = color;
}