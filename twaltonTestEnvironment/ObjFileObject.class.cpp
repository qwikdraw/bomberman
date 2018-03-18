
#include "ObjFileObject.class.hpp"

void	ObjFileObject::Load(void)
{
	glUseProgram(_program->ID());

	glGenBuffers(1, &_uvArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, _uvArrayID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLfloat) * _objectArrays.GetUVMap().size(),
		     &(_objectArrays.GetUVMap()[0]),
		     GL_STATIC_DRAW);

	glGenBuffers(1, &_normalArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, _normalArrayID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLfloat) * _objectArrays.GetNormals().size(),
		     &(_objectArrays.GetNormals()[0]),
		     GL_STATIC_DRAW);

	glGenBuffers(1, &_vertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLfloat) * _objectArrays.GetVertices().size(),
		     &(_objectArrays.GetVertices()[0]),
		     GL_STATIC_DRAW);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexImage2D(GL_TEXTURE_2D,
		     0,
		     GL_RGB,
		     _textureParser.Width(),
		     _textureParser.Height(),
		     0,
		     GL_BGR,
		     GL_UNSIGNED_BYTE,
		     _textureParser.Data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(_textureLocationID, 0);
}

void	ObjFileObject::Unload(void)
{
	glDeleteBuffers(1, &_uvArrayID);
	glDeleteBuffers(1, &_normalArrayID);
	glDeleteBuffers(1, &_vertexArrayID);
	
	glDeleteTextures(1, &_textureID);
}

ObjFileObject::ObjFileObject(std::string objectPath,
			     std::string texturePath)
	: _objectArrays(objectPath),
	  _textureParser(texturePath)
{
	_transform = glm::mat4(1);
        _program = new ShadingProgram(OBJ_VERTEX_SHADER_PATH, "",
				      OBJ_FRAGMENT_SHADER_PATH);
	_perspectiveID = glGetUniformLocation(_program->ID(), "perspective");
	_transformID = glGetUniformLocation(_program->ID(), "transform");
	_textureLocationID = glGetUniformLocation(_program->ID(), "tex");
	Load();
}

void	ObjFileObject::UsePerspective(glm::mat4 m)
{
	_program->Use();
	glUniformMatrix4fv(_perspectiveID,
			1,
			GL_FALSE,
			glm::value_ptr(m));
}

void	ObjFileObject::SetTransform(glm::mat4 m)
{
	_program->Use();
	_transform = m;
	glUniformMatrix4fv(_transformID,
			1,
			GL_FALSE,
			glm::value_ptr(m));
}

void	ObjFileObject::Render(void)
{
	_program->Use();
	
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _normalArrayID);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _uvArrayID);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, _objectArrays.GetVertices().size() / 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
