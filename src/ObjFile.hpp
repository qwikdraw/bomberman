#pragma once

#include "bomberman.hpp"
#include "ObjFileArrayExtractor.hpp"
#include "Texture.hpp"
#include "Light.hpp"
#include "ShadingProgram.hpp"

#define OBJ_VERTEX_SHADER_PATH "src/objVertex.glsl"
#define OBJ_FRAGMENT_SHADER_PATH "src/objFrag.glsl"

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
	
	glm::mat4 _transform;
	
	void	Load(void);
	void	Unload(void);

public:
	ObjFile(std::string objectPath, std::string texturePath);
	virtual ~ObjFile(void);

	void	UseMaterial(float specular, float fog, glm::vec3 fogcol, float diffuse);
	void	UsePerspective(std::pair<glm::mat4, glm::mat4>);
	void	SetTransform(glm::mat4);
	void	Render(void);
	void	Render(glm::vec3);
};
