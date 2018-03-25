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

	//! Use the given lookAt matrix
	void	UseLookAt(glm::mat4 m);

	//! Use the given projection matrix
	void	UseProjection(glm::mat4 m);
	
	//! Set the transform matrix to be applied to the particles
	void	SetTransform(glm::mat4 m);

	//! Returns a vector of size 4N floats - where N is the number of particles
	/*!
	Each set of 4 floats is to be interpreted as a set of physical attributes
	that corrispond to a single particle. The first 3 floats corrispond to (x, y, z)
	position, and the 4th float corrisponds to the particle size.
	 */
	std::vector<float>	&GetPhysicalAttributes(void);

	//! Returns a vector of size 4N floats
	/*!
	each set of 4 floats corrisponds to an RGBA color of a single particle.
	 */
	std::vector<float>	&GetColorAttributes(void);

	//! Returns a vector of size N indices.
	/*!
	Initially this contains indices [0 ... N-1], however when the Sort() method is called,
	the particle positions in the arrays will change. The Indices array will also change so
	you can still refer to the same particle via its attribute index. Example: if a particle is
	in GetPhysicalAttributes()[3], then GetAttributeIndices()[3] will return its original index
	before any sorting took place.
	 */
	std::vector<size_t>	&GetAttributeIndices(void);

	//! Sorts the particles based on Z values.
	/*!
	This should only be used if there are noticable artifacts with transparent particles,
	since the operation is expensive and will force you to use GetAttributeIndices() if you
	want to store additional particle infomation.
	 */
	void	Sort(void);

	//! Saves the current physical and color attributes onto the GPU, ready for rendering.
	void	Update(void);

	//! Renders the particles.
	void	Render(void);
};

#endif
