#ifndef PARTICLES_CLASS_HPP
#define PARTICLES_CLASS_HPP

#include "voxGL.hpp"

#define PARTICLE_VERTEX_SHADER_PATH "src/particleVertex.glsl"
#define PARTICLE_FRAGMENT_SHADER_PATH "src/particleFrag.glsl"

class Particles
{

private:

	ShadingProgram *_program;

	GLuint _perspectiveID;
	GLuint _transformID;
	
	int _amount;
	
	std::vector<float> _vertices;
	std::vector<float> _positionArray;
	std::vector<float> _colorArray;
	
	GLuint _baseShapeID;
	GLuint _particlePositionsID;
	GLuint _particleColorsID;
	
public:
	
	Particles(int amount);

	void	UsePerspective(glm::mat4 m);
	void	SetTransform(glm::mat4 m);
	
	std::vector<float>	&GetPhysicalAttributes(void);
	std::vector<float>	&GetColorAttributes(void);
	void	Update(void);
	void	Render(void);
};

#endif
