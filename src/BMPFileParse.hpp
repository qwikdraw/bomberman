#ifndef BMPFILEPARSE_HPP
#define BMPFILEPARSE_HPP

#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>

class	BMPFileParse
{
private:
	
	std::vector<unsigned char> _imageData;
	int _width;
	int _height;
	int _offset;
	
public:

	BMPFileParse(std::string filepath);

	int	Width(void);
	int	Height(void);
	unsigned char	*Data(void);
};

#endif
