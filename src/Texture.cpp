
#include "Texture.hpp"

Texture::Texture(std::string filepath)
{
	unsigned error = lodepng::decode(_imageData, _width, _height, filepath.c_str());

	if (error)
		std::cout << "error: " << lodepng_error_text(error) << std::endl;
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
