#ifndef PARTICLES_CLASS_HPP
#define PARTICLES_CLASS_HPP

#include "voxGL.hpp"
#include <numeric>

#define PARTICLE_VERTEX_SHADER_PATH "src/particleVertex.glsl"
#define PARTICLE_FRAGMENT_SHADER_PATH "src/particleFrag.glsl"

class Particles
{

private:

	ShadingProgram *_program;

	GLuint _lookAtID;
	GLuint _viewID;
	GLuint _transformID;

	glm::mat4 _lookAt;
	glm::mat4 _view;
	
	int _amount;
	
	std::vector<float> _vertices;
	std::vector<float> _positionArray;
	std::vector<float> _colorArray;
	std::vector<size_t> _indices;
	
	GLuint _baseShapeID;
	GLuint _particlePositionsID;
	GLuint _particleColorsID;

	
public:
	
	Particles(int amount);

	void	UsePerspective(std::pair<glm::mat4, glm::mat4> m);
	void	SetTransform(glm::mat4 m);
	
	std::vector<float>	&GetPhysicalAttributes(void);
	std::vector<float>	&GetColorAttributes(void);
	std::vector<size_t>	&GetAttributeIndices(void);
	void	Sort(void);
	void	Update(void);
	void	Render(void);
};

#endif
