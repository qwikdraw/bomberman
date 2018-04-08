
#include "BMPFileParse.hpp"

BMPFileParse::BMPFileParse(std::string filepath)
{
	std::ifstream file(filepath);

	if (!file)
	{
		std::cout << "bad filepath" << std::endl;
		exit(1);
	}
	file.seekg(0, std::ios::end);
	std::streampos length = file.tellg();
	file.seekg(0, std::ios::beg);

	_imageData.resize(length);
	file.read(reinterpret_cast<char*>(&_imageData[0]), length);

	unsigned char *width = &_imageData[0] + 18;
	unsigned char *height = &_imageData[0] + 22;
	unsigned char *offset = &_imageData[0] + 10;

	std::memcpy(&_width, width, sizeof(int));
	std::memcpy(&_height, height, sizeof(int));
	std::memcpy(&_offset, offset, sizeof(int));
}

int	BMPFileParse::Width(void)
{
	return _width;
}

int	BMPFileParse::Height(void)
{
	return _height;
}

unsigned char	*BMPFileParse::Data(void)
{
	return &_imageData[0] + _offset;
}
