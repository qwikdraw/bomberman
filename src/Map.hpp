#ifndef MAP_HPP
#define MAP_HPP

#include "AnimatedObject.hpp"

#define BLOCK_MODEL "src/mapfile.aniobj"
#define FLOOR_MODEL "src/mapfile.aniobj"

class	Map
{
private:

	std::vector<std::vector<int> > _blockTypes;
	AnimatedObject _block;
	AnimatedObject _floor;
	
public:

	Map(std::string mapfile);
	
	void	Render(std::pair<glm::mat4, glm::mat4> perspective);
};

#endif
