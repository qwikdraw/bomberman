
#include "ObjFileArrayExtractor.class.hpp"

void	ObjFileArrayExtractor::Parse_v(std::stringstream &ss)
{
	std::string temp;
	float val;

	ss >> temp;
	std::stringstream(temp) >> val;
	temp = "";
	_vertices.push_back(val);
	ss >> temp;
	std::stringstream(temp) >> val;
	temp = "";
	_vertices.push_back(val);
	ss >> temp;
	std::stringstream(temp) >> val;
	temp = "";
	_vertices.push_back(val);
}

void	ObjFileArrayExtractor::Parse_vn(std::stringstream &ss)
{
	std::string temp;
	float val;
	
	ss >> temp;
	std::stringstream(temp)	>> val;
	temp = "";
	_normals.push_back(val);
	ss >> temp;
	std::stringstream(temp)	>> val;
	temp = "";
	_normals.push_back(val);
	ss >> temp;
	std::stringstream(temp)	>> val;
	temp = "";
	_normals.push_back(val);
}

void	ObjFileArrayExtractor::Parse_vt(std::stringstream &ss)
{
	std::string temp;
	float val;
	
	ss >> temp;
	std::stringstream(temp)	>> val;
	temp = "";
	_uvMap.push_back(val);
	ss >> temp;
	std::stringstream(temp)	>> val;
	temp = "";
	_uvMap.push_back(val);
}

void	ObjFileArrayExtractor::Parse_f(std::stringstream &ss)
{
	std::string temp;

	for (int i = 0; i < 3; i++)
	{
		Point p;
		
		ss >> temp;
		std::stringstream token(temp);

		token >> p.vertex;
		token.ignore();
		token >> p.texture;
		token.ignore();
		token >> p.normal;
		_faces.push_back(p);
	}
}

ObjFileArrayExtractor::ObjFileArrayExtractor(std::string filename)
{
	std::ifstream file(filename);

	if (!file)
	{
		std::cout << filename << " path was invalid" << std::endl;
		throw "InvalidFilePath";
	}

	std::string line;
	std::string temp;

	while (std::getline(file, line))
	{
		std::stringstream ss;

		ss << line;
		ss >> temp;
		if (temp == "v")
			Parse_v(ss);
		else if (temp == "vn")
			Parse_vn(ss);
		else if (temp == "vt")
			Parse_vt(ss);
		else if (temp == "f")
			Parse_f(ss);
		temp = "";
	}
	
	for (auto &p : _faces)
	{
		_verticesOut.push_back(_vertices[p.vertex * 3 - 3]);
		_verticesOut.push_back(_vertices[p.vertex * 3 - 2]);
		_verticesOut.push_back(_vertices[p.vertex * 3 - 1]);

		_normalsOut.push_back(_normals[p.normal * 3 - 3]);
		_normalsOut.push_back(_normals[p.normal * 3 - 2]);
		_normalsOut.push_back(_normals[p.normal * 3 - 1]);

		_uvMapOut.push_back(_uvMap[p.texture * 2 - 2]);
		_uvMapOut.push_back(_uvMap[p.texture * 2 - 1]);
	}

	for (auto i : _vertices)
		std::cout << i << " ";
	std::cout << std::endl;
	for (auto i : _normals)
		std::cout << i << " ";
	std::cout << std::endl;
	for (auto i : _uvMap)
		std::cout << i << " ";
	std::cout << std::endl;
	for (auto i : _faces)
		std::cout << i.vertex << "," << i.normal << "," << i.texture << " ";
	std::cout << std::endl;
}

std::vector<float>	&ObjFileArrayExtractor::GetVertices(void)
{
	return _verticesOut;
}

std::vector<float>	&ObjFileArrayExtractor::GetNormals(void)
{
	return _normalsOut;
}

std::vector<float>	&ObjFileArrayExtractor::GetUVMap(void)
{
	return _uvMapOut;
}
