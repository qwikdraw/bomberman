
#include "Grid.class.hpp"

void	Grid::initLines(void)
{
	
	for (float x = -_len / 2; x <= _len / 2; x++)
	{
		glm::vec3 p1 = {x * _size, 0, -(_len / 2) * _size};
		glm::vec3 p2 = {x * _size, 0, (_len / 2) * _size};

		p1 = glm::vec3(_transform * glm::vec4(p1, 1)) + _center;
		p2 = glm::vec3(_transform * glm::vec4(p2, 1)) + _center;
		
		_lines.insert(_lines.end(), &p1.x, &p1.x + 3);
		_lines.insert(_lines.end(), &p2.x, &p2.x + 3);
	}

	for (float z = -_len / 2; z <= _len / 2; z++)
	{
		glm::vec3 p1 = {-(_len / 2) * _size, 0, z * _size};
		glm::vec3 p2 = {(_len / 2) * _size, 0, z * _size};

		p1 = glm::vec3(_transform * glm::vec4(p1, 1)) + _center;
		p2 = glm::vec3(_transform * glm::vec4(p2, 1)) + _center;
		
		_lines.insert(_lines.end(), &p1.x, &p1.x + 3);
		_lines.insert(_lines.end(), &p2.x, &p2.x + 3);
	}
}

Grid::Grid(float squareSize,
	   float squareLen,
	   glm::vec3 center,
	   glm::mat4 transform)
	: _size(squareSize),
	  _len(squareLen),
	  _center(center),
	  _transform(transform)
{
	_program = new ShadingProgram(GRID_VERTEX_SHADER_PATH, "",
				      GRID_FRAGMENT_SHADER_PATH);
	_perspectiveID = glGetUniformLocation(_program->ID(), "perspective");
	initLines();
	
	glGenBuffers(1, &_linesID);
	glBindBuffer(GL_ARRAY_BUFFER, _linesID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLfloat) * _lines.size(),
		     &_lines[0],
		     GL_STATIC_DRAW);	
}

Grid::~Grid(void)
{
	glDeleteBuffers(1, &_linesID);
}

void	Grid::NewPerspective(glm::mat4 m)
{
	_program->Use();

	glUniformMatrix4fv(_perspectiveID,
			   1,
			   GL_FALSE,
			   glm::value_ptr(m));
}

void	Grid::Render(void)
{
	_program->Use();
	
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBindBuffer(GL_ARRAY_BUFFER, _linesID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glDrawArrays(GL_LINES, 0, _lines.size() / 3);
	
	glDisableVertexAttribArray(0);

	glDisable(GL_BLEND);
}
