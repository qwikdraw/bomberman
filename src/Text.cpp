#include "Text.hpp"

ShadingProgram		*Text::_program = nullptr;
std::vector<float>	Text::_square;
std::vector<float>	Text::_uv;
GLuint			Text::_squareID;
GLuint			Text::_UVID;
GLuint			Text::_textureID;
GLuint			Text::_textureLocationID;
bool			Text::_init = false;

Text::Text(std::string message)
{

	_message = message;
	if (_init)
		return;

	_program = new ShadingProgram(TEXT_VERTEX_SHADER_PATH, "",
				      TEXT_FRAGMENT_SHADER_PATH);
	
	_square.resize(12);
	_uv.resize(12);

	_textureLocationID = glGetUniformLocation(_program->ID(), "tex");
	glUseProgram(_program->ID());
	
	glGenBuffers(1, &_squareID);	
	glBindBuffer(GL_ARRAY_BUFFER, _squareID);
	glBufferData(GL_ARRAY_BUFFER,
		     2 * 6 * sizeof(GLfloat),
		     NULL,
		     GL_STREAM_DRAW);
	
	glGenBuffers(1, &_UVID);
	glBindBuffer(GL_ARRAY_BUFFER, _UVID);
	glBufferData(GL_ARRAY_BUFFER,
		     12 * sizeof(GLfloat),
		     NULL,
		     GL_STREAM_DRAW);

	Texture textureParser(FONT_FILE);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexImage2D(GL_TEXTURE_2D,
		     0,
		     GL_RGBA,
		     textureParser.Width(),
		     textureParser.Height(),
		     0,
		     GL_RGBA,
		     GL_UNSIGNED_BYTE,
		     textureParser.Data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(_textureLocationID, 0);

	_init = true;
}

void	Text::RenderChar(char c, glm::vec2 topleft, glm::vec2 botright)
{

	glm::vec2 topleftUV((c % 16) / 16.0f, (16 - (c / 16)) / 16.0f);
	glm::vec2 botrightUV(topleftUV.x + 1 / 16.0f, topleftUV.y - 1 / 16.0f);
	
	_square[0] = topleft.x; _square[1] = topleft.y;
	_square[2] = topleft.x; _square[3] = botright.y;
	_square[4] = botright.x; _square[5] = botright.y;

	_square[6] = topleft.x; _square[7] = topleft.y;
	_square[8] = botright.x; _square[9] = topleft.y;
	_square[10] = botright.x; _square[11] = botright.y;


	_uv[0] = topleftUV.x; _uv[1] = topleftUV.y;
	_uv[2] = topleftUV.x; _uv[3] = botrightUV.y;
	_uv[4] = botrightUV.x; _uv[5] = botrightUV.y;

	_uv[6] = topleftUV.x; _uv[7] = topleftUV.y;
	_uv[8] = botrightUV.x; _uv[9] = topleftUV.y;
	_uv[10] = botrightUV.x; _uv[11] = botrightUV.y;

	glBindBuffer(GL_ARRAY_BUFFER, _squareID);
	glBufferData(GL_ARRAY_BUFFER,
		     12  * sizeof(GLfloat),
		     NULL,
		     GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER,
			0,
			12 * sizeof(GLfloat),
			&_square[0]);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _UVID);
	glBufferData(GL_ARRAY_BUFFER,
		     12 * sizeof(GLfloat),
		     NULL,
		     GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER,
			0,
			12 * sizeof(GLfloat),
			&_uv[0]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void	Text::Render(float aspect)
{


//	float screenWidth = aspect;
//	float screenHeight = 1;

	float charWidth = 1 / aspect;
	float charHeight = 1;

	float totalChars = _message.length();	


	float totalWidth = charWidth * totalChars;
	float totalHeight = 1;


	float charScale = fmin(2 / totalWidth, 2 / totalHeight);

	charWidth *= charScale;
	charHeight *= charScale;

	_program->Use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, _textureID);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(_textureLocationID, 0);
	
	for (size_t i = 0; i < _message.length(); i++)
	{
		float distFromCenter = i - static_cast<float>(_message.length() - 1) / 2;
		
		float xCenter =	distFromCenter * charWidth * 0.8;

		RenderChar(_message[i],
			   glm::vec2(xCenter - charWidth / 2, charHeight / 2),
			   glm::vec2(xCenter + charWidth / 2, -charHeight / 2));
	}

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	
}
