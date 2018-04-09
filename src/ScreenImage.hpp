#ifndef SCREENIMAGE_HPP
#define SCREENIMAGE_HPP

#define SCREENIMAGE_VERTEX_SHADER_PATH "../LowLevelDraw/screenImageVertex.glsl"
#define SCREENIMAGE_FRAGMENT_SHADER_PATH "../LowLevelDraw/screenImageFrag.glsl"

#include "voxGL.hpp"
#include "BMPFileParse.class.hpp"
#include <vector>

class	ScreenImage
{
private:

	static const std::vector<float> _vertexArray;
	static const std::vector<float> _uvArray;
	
	ShadingProgram *_program;
	BMPFileParse _textureParser;
	GLuint _vertexArrayID;
	GLuint _uvArrayID;
	GLuint _textureID;
	GLuint _textureLocationID;	
							
	
public:

	ScreenImage(std::string imagepath);
	virtual ~ScreenImage(void);

	void	Render(void);
};

#endif
