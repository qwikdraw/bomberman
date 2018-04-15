#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

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
	ObjFileArrayExtractor(std::string filename);

	std::vector<float> &GetVertices(void);
	std::vector<float> &GetNormals(void);
	std::vector<float> &GetUVMap(void);
};
