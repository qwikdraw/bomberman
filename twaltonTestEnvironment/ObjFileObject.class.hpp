#ifndef OBJFILEOBJECT_CLASS_HPP
#define OBJFILEOBJECT_CLASS_HPP

#include "voxGL.hpp"
#include "ObjFileArrayExtractor.class.hpp"

#define OBJ_VERTEX_SHADER_PATH "objVertex.glsl"
#define OBJ_FRAGMENT_SHADER_PATH "objFrag.glsl"

class	ObjFileObject
{
private:

	ShadingProgram *_program;
	ObjFileArrayExtractor _objectArrays;
	GLuint _uvArrayID;
	GLuint _normalArrayID;
	GLuint _vertexArrayID;
	GLuint _perspectiveID;
	GLuint _transformID;	
	GLuint _textureID;
	GLuint _textureLocationID;

	glm::mat4 _transform;
	
	void	Load(void);
	void	Unload(void);
	
public:
	
	ObjFileObject(std::string objectPath, std::string texturePath);

	void	UsePerspective(glm::mat4);
	void	SetTransform(glm::mat4);
	void	Render(void);
};

#endif
