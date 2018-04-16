
#include "Map.hpp"

Map::Map(std::string mapfile) : _block(BLOCK_MODEL),
				_floor(FLOOR_MODEL)
{
	std::ifstream file(mapfile);

	if (!file)
	{
		std::cout << "bad filepath: " << mapfile << std::endl;
		exit(1);
	}

	for (std::string line; std::getline(file, line); )
	{
		std::stringstream ss(line);
		std::string temp;
		int found;
		std::vector<int> v;
		
		while (!ss.eof())
		{
			ss >> temp;
			if (std::stringstream(temp) >> found)
				v.push_back(found);
			temp = "";
		}
		_blockTypes.push_back(v);
	}
}

void	Map::Render(std::pair<glm::mat4, glm::mat4> perspective)
{
	_block.UsePerspective(perspective);
	_floor.UsePerspective(perspective);

	for (size_t y = 0; y < _blockTypes.size(); y++)
	{
		for (size_t x = 0; x < _blockTypes[y].size(); x++)
		{
			if (_blockTypes[y][x] == 0)
			{
				_floor.MoveTo(glm::vec3(x, y, 0));
				_floor.Render();
			}
			else
			{
				_block.MoveTo(glm::vec3(x, y, 0));
				_block.Render();
			}
		}
	}
}
