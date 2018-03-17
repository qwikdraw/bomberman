
#include "BMPFileParse.class.hpp"

BMPFileParse::BMPFileParse(std::string filepath)
{
	std::ifstream file(filepath);

	if (!file)
	{
		std::cout << "bad filepath" << std::endl;
		exit(1);
	}
	file.seekg(0, std::ios::end);
	streampos length = file.tellg();
	file.seekg(0, std::ios::beg);

	_imageData.resize(length);
	file.read(&_imageData[0], length);
}
