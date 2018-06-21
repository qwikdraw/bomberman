#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

//! Used for parsing obj files
class	ObjFileArrayExtractor
{

struct Point
{
	int vertex;
	int normal;
	int texture;
};

	std::vector<float> _vertices;
	std::vector<float> _normals;
	std::vector<float> _uvMap;
	std::vector<Point> _faces;

	std::vector<float> _verticesOut;
	std::vector<float> _normalsOut;
	std::vector<float> _uvMapOut;

	void	Parse_v(std::stringstream&);
	void	Parse_vn(std::stringstream&);
	void	Parse_vt(std::stringstream&);
	void	Parse_f(std::stringstream&);

public:
	//! extract all the infomation
	ObjFileArrayExtractor(std::string filename);

	//! size of this vector is always divisible by 3
	std::vector<float> &GetVertices(void);
	//! size also is always divisible by 3
	std::vector<float> &GetNormals(void);
	//! size of this vector is always divisible by 2
	std::vector<float> &GetUVMap(void);
};
