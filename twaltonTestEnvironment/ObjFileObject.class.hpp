#ifndef OBJFILEOBJECT_CLASS_HPP
#define OBJFILEOBJECT_CLASS_HPP

#include "voxGL.hpp"
#include "ObjFileArrayExtractor.class.hpp"

class	ObjFileObject
{
private:
	
	ObjFileArrayExtractor _objectArrays;
	GLuint _uvArrayID;
	GLuint _normalArrayID;
	GLuint _vertexArrayID;
	GLuint _perspectiveID;
	GLuint _transformID;
	GLuint _textureID;

	glm::mat4 _transform;
	
	void	Load(void);
	void	Unload(void);
	
public:
	
	ObjFileObject(std::string filepath);

	void	UsePerspective(glm::mat4);
	void	SetTransform(glm::mat4);
	void	Render(void);
};

#endif
