#ifndef VOXRENDERER_CLASS_HPP
#define VOXRENDERER_CLASS_HPP

#include "voxGL.hpp"

class	VoxRenderer
{
private:

	static const int size = 1000;
	
	ShadingProgram *_program;
	GLuint _perspectiveID;
	GLuint _transformID;
	glm::mat4 _perspective;
	std::vector<VoxObject*> _objects;

public:

	VoxRenderer(void);

	void	AttachObject(VoxObject *object);
	void	DetachObject(VoxObject *object);
	void	Render(void);
	void	NewPerspective(glm::mat4);
};

#endif
