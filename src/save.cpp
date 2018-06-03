#include "save.hpp"

void	save::updateLevel(std::string level)
{
	std::ifstream savefileIn("savefile");
	std::stringstream buf;
	buf << savefileIn.rdbuf();
	std::string save = buf.str();
	save = save.length() == 8 ? save : "Level:01";
	savefileIn.close();
	size_t levelStrBegin = save.find("Level:") + 6;
	size_t levelStrEnd = save.find('\n', levelStrBegin);
	std::string saveLevel = save.substr(levelStrBegin, levelStrEnd);
	
	if (saveLevel.compare(level) < 0)
	{
		save.replace(levelStrBegin, levelStrEnd - levelStrBegin, level);
		std::ofstream savefileOut("savefile", std::ios_base::trunc);
		savefileOut << save;
		savefileOut.close();
	}
}

std::string	save::getLevel(void)
{
	std::ifstream savefileIn("savefile");
	std::stringstream buf;
	buf << savefileIn.rdbuf();
	std::string save = buf.str();
	save = save.length() == 8 ? save : "Level:01";
	savefileIn.close();
	size_t levelStrBegin = save.find("Level:") + 6;
	size_t levelStrEnd = save.find('\n', levelStrBegin);
	std::string saveLevel = save.substr(levelStrBegin, levelStrEnd);

	return saveLevel;
}
