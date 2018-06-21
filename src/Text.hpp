#pragma once

#include "bomberman.hpp"
#include "ShadingProgram.hpp"
#include "Texture.hpp"

#define TEXT_VERTEX_SHADER_PATH "src/shaders/textVertex.glsl"
#define TEXT_FRAGMENT_SHADER_PATH "src/shaders/textFrag.glsl"

#define FONT_FILE "assets/textures/game_font.png"

//! Used for drawing 2D text
class	Text
{
private:

	static ShadingProgram *_program;
	
	std::string _message;
	
	static std::vector<float> _square;
	static std::vector<float> _uv;
	
	static GLuint _squareID;
	static GLuint _UVID;
	static GLuint _textureID;
	static GLuint _textureLocationID;

	static bool _init;
	
	void	RenderChar(char c, glm::vec2 topleft, glm::vec2 botright);
	
public:

	//! initialize the text with given string
	Text(std::string message);

	//! render the string to fill up as much of the render zone as possible with given aspect ratio
	void	Render(float aspect);
};
