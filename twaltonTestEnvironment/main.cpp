
#include "ObjFileArrayExtractor.class.hpp"

int	main(int ac, char **av)
{
	ObjFileArrayExtractor extract("test.obj");

	std::vector<float> vertices = extract.GetVertices();
	std::vector<float> normals = extract.GetNormals();
	std::vector<float> uvMap = extract.GetUVMap();

	for (auto i : vertices)
		std::cout << i << " ";
	std::cout << std::endl << std::endl;	
	
        for (auto i : normals)
	        std::cout << i << " ";
        std::cout << std::endl << std::endl;
	
        for (auto i : uvMap)
	        std::cout << i << " ";
        std::cout << std::endl;


	std::cout << vertices.size() << " " << normals.size() << " " << uvMap.size() << std::endl;
}
