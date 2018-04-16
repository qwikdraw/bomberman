
#pragma once

#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include "lodepng.h"

class	Texture
{
private:
	
	std::vector<unsigned char> _imageData;
	unsigned _width;
	unsigned _height;
	
public:

	//! Only supports png currently
	Texture(std::string filepath);

	unsigned	Width(void);
	unsigned	Height(void);
	unsigned char	*Data(void);
};
