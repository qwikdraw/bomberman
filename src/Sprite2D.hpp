#pragma once

#define SCREENIMAGE_VERTEX_SHADER_PATH "src/shaders/screenImageVertex.glsl"
#define SCREENIMAGE_FRAGMENT_SHADER_PATH "src/shaders/screenImageFrag.glsl"

#include "bomberman.hpp"
#include "Texture.hpp"
#include "ShadingProgram.hpp"
#include <vector>

//! Used for rendering texture to screen
class	Sprite2D
{
private:

	static const std::vector<float> _vertexArray;
	static const std::vector<float> _uvArray;
	
	ShadingProgram *_program;
	Texture _textureParser;
	GLuint _vertexArrayID;
	GLuint _uvArrayID;
	GLuint _textureID;
	GLuint _textureLocationID;	
							
	
public:

	//! loads the texture from the file
	Sprite2D(std::string imagepath);
	virtual ~Sprite2D(void);

	//! renders the texture to the set render zone
	void	Render(void);
};
