#pragma once

#include "bomberman.hpp"
#include "ObjFileArrayExtractor.hpp"
#include "Texture.hpp"
#include "Light.hpp"
#include "ShadingProgram.hpp"

#define OBJ_VERTEX_SHADER_PATH "src/shaders/objVertex.glsl"
#define OBJ_FRAGMENT_SHADER_PATH "src/shaders/objFrag.glsl"

//! Renders a .obj file - but should never be interacted with, only Model uses this
class	ObjFile
{
	ShadingProgram *_program;
	ObjFileArrayExtractor _objectArrays;
	Texture _textureParser;
	GLuint _uvArrayID;
	GLuint _normalArrayID;
	GLuint _vertexArrayID;
	GLuint _projectionID;
	GLuint _lookAtID;
	GLuint _transformID;	
	GLuint _textureID;
	GLuint _textureLocationID;
	GLuint _lightPosID;
	GLuint _lightColorID;
	GLuint _lightFalloffID;
	GLuint _lightNumID;
	
	glm::mat4 _transform;
	
	void	Load(void);
	void	Unload(void);

public:
	//! load the obj file and texture from their files
	ObjFile(std::string objectPath, std::string texturePath);
	virtual ~ObjFile(void);

	//! adjust various constants used in the shader
	void	UseMaterial(float specular, float fog, glm::vec3 fogcol, float diffuse);
	//! will ensure the object is rendered with this perspective
	void	UsePerspective(std::pair<glm::mat4, glm::mat4>);
	//! will ensure object is rendered with this transform
	void	SetTransform(glm::mat4);
	//! renders the object to 0, 0, 0
	void	Render(void);
	//! renders the object to the position given as argument
	void	Render(glm::vec3);
};
