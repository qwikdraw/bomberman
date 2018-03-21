
#include "TestMap.class.hpp"

TestMap::TestMap(void) : _mapBlock("mapblock.obj", "Tulips.bmp")
{	
}

void	TestMap::UsePerspective(glm::mat4 m)
{
	_perspective = m;
}

void	TestMap::Render(void)
{
//just going to render a 10x10 map

	_mapBlock.UsePerspective(_perspective);
	
	for (int x = 0; x < 10; x++)
	{
		for (int z = 0; z < 10; z++)
		{
			_mapBlock.SetTransform(glm::translate(glm::vec3(x * 2, 0, z * 2)));
			_mapBlock.Render();
		}
	}
}
