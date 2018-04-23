#pragma once

#include "bomberman.hpp"
#include "ShadingProgram.hpp"
#include "Texture.hpp"

#define TEXT_VERTEX_SHADER_PATH "src/textVertex.glsl"
#define TEXT_FRAGMENT_SHADER_PATH "src/textFrag.glsl"

#define FONT_FILE "assets/textures/game_font.png"

class	Text
{
private:

	ShadingProgram *_program;
	Texture _textureParser;
	std::string _message;
	std::vector<float> _square;
	std::vector<float> _uv;
	
	GLuint _squareID;
	GLuint _UVID;
	GLuint _textureID;
	GLuint _textureLocationID;

	void	RenderChar(char c, glm::vec2 topleft, glm::vec2 botright);
	
public:

	Text(std::string message);
	~Text(void);
	
	void	Render(float aspect);
};
