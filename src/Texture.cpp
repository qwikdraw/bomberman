
#include "Texture.hpp"

Texture::Texture(std::string filepath)
{
	unsigned error = lodepng::decode(_imageData, _width, _height, filepath.c_str());

	if (error)
		std::cout << "error: " << lodepng_error_text(error) << std::endl;

	std::vector<unsigned char> temp(_width * 4);
	
	for (size_t i = 0; i < _height / 2; i++)
	{
		std::memmove(&temp[0], &_imageData[i * _width * 4], _width * 4);
		std::memmove(&_imageData[i * _width * 4], &_imageData[(_height - i - 1) * _width * 4], _width * 4);
		std::memmove(&_imageData[(_height - i - 1) * _width * 4], &temp[0], _width * 4);
	}
}

unsigned	Texture::Width(void)
{
	return _width;
}

unsigned	Texture::Height(void)
{
	return _height;
}

unsigned char	*Texture::Data(void)
{
	return &_imageData[0];
}
