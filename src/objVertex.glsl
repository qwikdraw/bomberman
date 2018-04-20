#version 410 core

#define MAX_LIGHTS 100

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 lookAt;
uniform vec3 lightPos[MAX_LIGHTS];
uniform vec3 lightColor[MAX_LIGHTS];
uniform float lightFalloff[MAX_LIGHTS];


out	ShapeData {
	vec2 uv;
	vec3 lightMod;
	float dist;
} Data;

vec3	GetLightModifier(vec3 v, vec3 n)
{
	vec3 ret = vec3(0, 0, 0);

	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		if (lightColor[i] == vec3(0, 0, 0))
			continue;
		vec3 ray = v - vec3(lookAt * vec4(lightPos[i], 1));
		float intensity = lightFalloff[i] / (lightFalloff[i] + length(ray));
		
		ret += max(dot(n, -normalize(ray)), 0.2) * lightColor[i] * intensity;

		vec3 reflect = normalize(ray) - 2 * n * dot(normalize(ray), n);
		
		float specular = dot(normalize(reflect), normalize(-v));

		if (specular > 0)
			ret += pow(specular, 10) * lightColor[i];

	}
	return ret;
}

void	main()
{
	vec3 actualNormal = normalize(vec3(lookAt * transform * vec4(normal, 0)));
	vec3 actualVertex = vec3(lookAt * transform * vec4(vertex, 1));

	Data.dist = length(actualVertex);
	Data.uv = uv;
	Data.lightMod = GetLightModifier(actualVertex, actualNormal);
	gl_Position = projection * lookAt * transform * vec4(vertex, 1);
}
