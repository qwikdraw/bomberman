
#include "ScreenImage.hpp"

const	std::vector<float> ScreenImage::_vertexArray = {1, -1, 0,
                                                        -1, -1, 0,
                                                        1, 1, 0,
                                                        -1, 1, 0,
                                                        -1, -1, 0,
                                                        1, 1, 0};

const	std::vector<float> ScreenImage::_uvArray = {1, 0,
                                                    0, 0,
                                                    1, 1,
                                                    0, 1,
                                                    0, 0,
                                                    1, 1};

ScreenImage::ScreenImage(std::string imagepath) : _textureParser(imagepath)
{
	_program = new ShadingProgram(SCREENIMAGE_VERTEX_SHADER_PATH, "",
				      SCREENIMAGE_FRAGMENT_SHADER_PATH);
	_textureLocationID = glGetUniformLocation(_program->ID(), "tex");
	glUseProgram(_program->ID());

	glGenBuffers(1, &_vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLfloat) * _vertexArray.size(),
		     &_vertexArray[0],
		     GL_STATIC_DRAW);

	glGenBuffers(1, &_uvArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, _uvArrayID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLfloat) * _uvArray.size(),
		     &_uvArray[0],
		     GL_STATIC_DRAW);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexImage2D(GL_TEXTURE_2D,
		     0,
		     GL_RGBA,
		     _textureParser.Width(),
		     _textureParser.Height(),
		     0,
		     GL_RGBA,
		     GL_UNSIGNED_BYTE,
		     _textureParser.Data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(_textureLocationID, 0);
}

ScreenImage::~ScreenImage(void)
{
	glDeleteTextures(1, &_textureID);
	glDeleteBuffers(1, &_vertexArrayID);
	glDeleteBuffers(1, &_uvArrayID);
}

void	ScreenImage::Render(void)
{
	_program->Use();

	glDisable(GL_DEPTH_TEST);
	
	glBindTexture(GL_TEXTURE_2D, _textureID);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(_textureLocationID, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _uvArrayID);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, _vertexArray.size() / 3);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);
}
