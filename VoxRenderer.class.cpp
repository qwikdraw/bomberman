
#include "voxGL.hpp"

VoxRenderer::VoxRenderer(void)
{
	_program = new ShadingProgram(VERTEX_PATH, "", FRAG_PATH);
	_perspectiveID = glGetUniformLocation(_program->ID(), "perspective");
	_transformID = glGetUniformLocation(_program->ID(), "transform");
}

void	VoxRenderer::AttachObject(VoxObject *object)
{
	_objects.push_back(object);
	object->TransformID() = _transformID;
}

void	VoxRenderer::DetachObject(VoxObject *object)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		if (object == _objects[i])
		{
			_objects.erase(_objects.begin() + i);
			return;
		}
	}
}

void	VoxRenderer::Render(void)
{
	_program->Use();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->Render();
	}
}

void	VoxRenderer::NewPerspective(glm::mat4 m)
{
	_program->Use();
	
	_perspective = m;
	glUniformMatrix4fv(_perspectiveID,
			   1,
			   GL_FALSE,
			   glm::value_ptr(_perspective));
}
