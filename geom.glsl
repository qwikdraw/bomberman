#version 410 core

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;

uniform mat4 transform;
uniform mat4 perspective;

in BlockData {
	int raw;
} Block[];

out VertexData {
	vec4 normal;
	vec3 color;
} VertexOut;

#define	top     16777216	//0b00000001000000000000000000000000;
#define	bot     33554432	//0b00000010000000000000000000000000;
#define	left    67108864	//0b00000100000000000000000000000000;
#define	right   134217728	//0b00001000000000000000000000000000;
#define	front   268435456	//0b00010000000000000000000000000000;
#define	back    536870912	//0b00100000000000000000000000000000;

void	main()
{

	if (Block[0].raw << 8 == 0)
		return;

	float blue = float( Block[0].raw % 256 ) / 255;
	float green = float( (Block[0].raw / 256) % 256 ) / 255;
	float red = float( (Block[0].raw / (256 * 256)) % 256 ) / 255;

	bool isup = !bool((Block[0].raw & top));
	bool isdown = !bool((Block[0].raw & bot));
	bool isleft = !bool((Block[0].raw & left));
	bool isright = !bool((Block[0].raw & right));
	bool isforward = !bool((Block[0].raw & front));
	bool isbackward = !bool((Block[0].raw & back));

	vec4 p = gl_in[0].gl_Position;

	//face up

	if (isup)
	{
	
	gl_Position = perspective * transform *	(p + vec4(0, 1, 0, 0));
	VertexOut.normal = transform * vec4(0, 1, 0, 0);
	VertexOut.color = vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 1, 0, 0));
	VertexOut.normal = transform * vec4(0, 1, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(0, 1, 1, 0));
	VertexOut.normal = transform * vec4(0, 1, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 1, 1, 0));
	VertexOut.normal = transform * vec4(0, 1, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	EndPrimitive();
	}

	
	//face down

	if (isdown)
	{
	
	gl_Position = perspective * transform *	(p + vec4(0, 0, 0, 0));
	VertexOut.normal = transform * vec4(0, -1, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(0, 0, 1, 0));
	VertexOut.normal = transform * vec4(0, -1, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 0, 0, 0));
	VertexOut.normal = transform * vec4(0, -1, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 0, 1, 0));
	VertexOut.normal = transform * vec4(0, -1, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	EndPrimitive();
	}

	//face left

	if (isleft)
	{

	gl_Position = perspective * transform *	(p + vec4(0, 1, 0, 0));
	VertexOut.normal = transform * vec4(-1, 0, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(0, 1, 1, 0));
	VertexOut.normal = transform * vec4(-1, 0, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(0, 0, 0, 0));
	VertexOut.normal = transform * vec4(-1, 0, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(0, 0, 1, 0));
	VertexOut.normal = transform * vec4(-1, 0, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	EndPrimitive();
	}

	//face right

	if (isright)
	{

	gl_Position = perspective * transform *	(p + vec4(1, 1, 0, 0));
	VertexOut.normal = transform * vec4(1, 0, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 0, 0, 0));
	VertexOut.normal = transform * vec4(1, 0, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 1, 1, 0));
	VertexOut.normal = transform * vec4(1, 0, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 0, 1, 0));
	VertexOut.normal = transform * vec4(1, 0, 0, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	EndPrimitive();
	}
	
	//face forward

	if (isforward)
	{

	gl_Position = perspective * transform *	(p + vec4(0, 0, 0, 0));
	VertexOut.normal = transform * vec4(0, 0, -1, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 0, 0, 0));
	VertexOut.normal = transform * vec4(0, 0, -1, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(0, 1, 0, 0));
	VertexOut.normal = transform * vec4(0, 0, -1, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 1, 0, 0));
	VertexOut.normal = transform * vec4(0, 0, -1, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	EndPrimitive();
	}
	
	//face backward

	if (isbackward)
	{

	gl_Position = perspective * transform *	(p + vec4(0, 0, 1, 0));
	VertexOut.normal = transform * vec4(0, 0, 1, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(0, 1, 1, 0));
	VertexOut.normal = transform * vec4(0, 0, 1, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 0, 1, 0));
	VertexOut.normal = transform * vec4(0, 0, 1, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	gl_Position = perspective * transform *	(p + vec4(1, 1, 1, 0));
	VertexOut.normal = transform * vec4(0, 0, 1, 0);
        VertexOut.color	= vec3(red, green, blue);
	EmitVertex();

	EndPrimitive();
	}
}