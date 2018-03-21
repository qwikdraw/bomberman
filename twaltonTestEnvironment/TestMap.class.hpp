#ifndef TESTMAP_CLASS_HPP
#define TESTMAP_CLASS_HPP

#include "LowLevelDraw.hpp"
#include "voxGL.hpp"

class	TestMap
{

private:

	ObjFileObject _mapBlock;
	glm::mat4 _perspective;
	
public:

	TestMap(void);
	
	void	UsePerspective(glm::mat4);
	void	Render(void);

	
};

#endif
