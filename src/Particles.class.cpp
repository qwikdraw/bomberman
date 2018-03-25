
#include "Particles.class.hpp"

Particles::Particles(int amount) : _amount(amount)
{
	_program = new ShadingProgram(PARTICLE_VERTEX_SHADER_PATH, "",
				      PARTICLE_FRAGMENT_SHADER_PATH);
	_lookAtID = glGetUniformLocation(_program->ID(), "lookAt");
	_viewID = glGetUniformLocation(_program->ID(), "view");
	_transformID = glGetUniformLocation(_program->ID(), "transform");

	SetTransform(glm::mat4(1));
	
	_vertices.resize(12);
	_vertices[0] = -0.5; _vertices[1] = -0.5; _vertices[2] = 0;
	_vertices[3] = -0.5; _vertices[4] = 0.5; _vertices[5] = 0;
	_vertices[6] = 0.5; _vertices[7] = -0.5; _vertices[8] = 0;
	_vertices[9] = 0.5; _vertices[10] = 0.5; _vertices[11] = 0;

	_positionArray.resize(4 * _amount);
	_colorArray.resize(4 * _amount);
	_indices.resize(_amount);
	std::iota(_indices.begin(), _indices.end(), 0);
	
	glGenBuffers(1, &_baseShapeID);
	glBindBuffer(GL_ARRAY_BUFFER, _baseShapeID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLfloat) * _vertices.size(),
		     &_vertices[0],
		     GL_STATIC_DRAW);

	glGenBuffers(1, &_particlePositionsID);
	glBindBuffer(GL_ARRAY_BUFFER, _particlePositionsID);
	glBufferData(GL_ARRAY_BUFFER,
		     _amount * 4 * sizeof(GLfloat),
		     NULL,
		     GL_STREAM_DRAW);

	glGenBuffers(1, &_particleColorsID);
	glBindBuffer(GL_ARRAY_BUFFER, _particleColorsID);
	glBufferData(GL_ARRAY_BUFFER,
		     _amount * 4 * sizeof(GLfloat),
		     NULL,
		     GL_STREAM_DRAW);	
}

void	Particles::UsePerspective(std::pair<glm::mat4, glm::mat4> m)
{
	_program->Use();

	_lookAt = m.first;
	_view = m.second;
	
	glUniformMatrix4fv(_lookAtID,
			   1,
			   GL_FALSE,
			   glm::value_ptr(_lookAt));
	glUniformMatrix4fv(_viewID,
			   1,
			   GL_FALSE,
			   glm::value_ptr(_view));
}

void	Particles::SetTransform(glm::mat4 m)
{
	_program->Use();
	glUniformMatrix4fv(_transformID,
			   1,
			   GL_FALSE,
			   glm::value_ptr(m));
}

std::vector<float>	&Particles::GetPhysicalAttributes(void)
{
	return _positionArray;
}

std::vector<float>	&Particles::GetColorAttributes(void)
{
	return _colorArray;
}

std::vector<size_t>	&Particles::GetAttributeIndices(void)
{
	return _indices;
}

void	Particles::Sort(void)
{
	std::vector<float> modifiedPosArray(_positionArray.size() / 4);

	for (size_t i = 0; i < _positionArray.size(); i+=4)
	{
		glm::vec4 p1 = {_positionArray[i],
				_positionArray[i + 1],
				_positionArray[i + 2],
				1};
		glm::vec4 p2 = _lookAt * p1;

		modifiedPosArray[i / 4] = p2.z;
	}

	std::vector<size_t> indices(modifiedPosArray.size());
	
	std::iota(indices.begin(), indices.end(), 0);
	std::sort(indices.begin(), indices.end(),
		  [&modifiedPosArray](size_t i, size_t j){return modifiedPosArray[i] < modifiedPosArray[j];});

	std::vector<float> tempPositions(_positionArray.size());
	std::vector<size_t> tempIndices(_indices.size());

	for (size_t i = 0; i < indices.size(); i++)
	{
		std::memmove(&tempPositions[0] + i * 4,
			     &_positionArray[0] + indices[i] * 4,
			     sizeof(float) * 4);
		tempIndices[i] = _indices[indices[i]];			     
	}
	std::memmove(&_positionArray[0], &tempPositions[0], sizeof(float) * _positionArray.size());
	std::memmove(&_indices[0], &tempIndices[0], sizeof(size_t) * _indices.size());
}

void	Particles::Update(void)
{
	_program->Use();
	
	glBindBuffer(GL_ARRAY_BUFFER, _particlePositionsID);
	glBufferData(GL_ARRAY_BUFFER,
		     _amount * 4 * sizeof(GLfloat),
		     NULL,
		     GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER,
			0,
			_amount * 4 * sizeof(GLfloat),
			&_positionArray[0]);

	glBindBuffer(GL_ARRAY_BUFFER, _particleColorsID);
	glBufferData(GL_ARRAY_BUFFER,
		     _amount * 4 * sizeof(GLfloat),
		     NULL,
		     GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER,
			0,
			_amount * 4 * sizeof(GLfloat),
			&_colorArray[0]);	
}

void	Particles::Render(void)
{
	_program->Use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _baseShapeID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _particlePositionsID);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, _particleColorsID);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, _amount);

	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
