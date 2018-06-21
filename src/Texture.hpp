
#pragma once

#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include "lodepng.h"

//! Used for parsing image files
class	Texture
{
private:
	
	std::vector<unsigned char> _imageData;
	unsigned _width;
	unsigned _height;
	
public:

	//! Only supports png currently
	Texture(std::string filepath);

	//! gets the with of texture
	unsigned	Width(void);
	//! gets the height of texture
	unsigned	Height(void);
	//! returns an array containing the texture stored as RGBA each a single byte	
	unsigned char	*Data(void);
};
