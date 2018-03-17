#ifndef BMPFILEPARSE_CLASS_HPP
#define BMPFILEPARSE_CLASS_HPP

class	BMPFileParse
{
private:
	
	std::vector<unsigned char> _imageData;
	
public:

	BMPFileParse(std::string filepath);

	void	Width(void);
	void	Height(void);
	unsigned char	*Data(void);
};

#endif
