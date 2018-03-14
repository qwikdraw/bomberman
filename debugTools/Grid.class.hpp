#ifndef GRID_CLASS_HPP
#define GRID_CLASS_HPP

#include "voxGL.hpp"

#define GRID_VERTEX_SHADER_PATH "../debugTools/gridVS.glsl"
#define GRID_FRAGMENT_SHADER_PATH "../debugTools/gridFS.glsl"

class	Grid
{
private:

	ShadingProgram *_program;
	float _size;
	float _len;
	glm::vec3 _center;
	glm::mat4 _transform;
	std::vector<GLfloat> _lines;
	GLuint _linesID;
	GLuint _perspectiveID;

	void	initLines(void);	
	
public:
	
	Grid(float squareSize = 1,
	     float squareLen = 100,
	     glm::vec3 center = glm::vec3(0, 0, 0),
	     glm::mat4 transform = glm::mat4(1));
	virtual ~Grid(void);
	
	void	NewPerspective(glm::mat4 m);
	void	Render(void);
};

#endif
