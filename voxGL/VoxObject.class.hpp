#ifndef VOXOBJECT_CLASS_HPP
#define VOXOBJECT_CLASS_HPP

#include "voxGL.hpp"

class	VoxObject
{
	struct AnimatedChunk
	{
		VoxelChunk *chunk;
		std::vector<glm::mat4> animaTransform;
		std::vector<float> animaTime;		
		float animaCycle;

		//the point a chunk will be moved to after all transformations are applied
		glm::vec3 chunkPos;

		//a transform matrix that is applied to each chunk prior to the animaTransform.
	        //useful for rotating/sizeing parts while keeping animations intact
		glm::mat4 relativeTransform;
	};

private:

	Time _time;
	std::vector<AnimatedChunk> _parts;
	float _totalTime;
	GLuint _transformID;

	//the world position of the object
	glm::vec3 _pos;

	//transform matrix will be applied before object is translated
	//so you can use simple rotation matricies to rotate object
	glm::mat4 _transform;

	std::string	ReadFile(std::string);

	glm::mat4	getRelativeTransform(std::string&);
	glm::vec3	getChunkPos(std::string&);
	AnimatedChunk	getAnimatedChunk(std::string&);
	float	getAnimaCycle(std::string&);
	VoxelChunk	*getChunk(std::string&);
	std::vector<float>	getAnimaTime(std::string&);
	std::vector<glm::mat4>	getAnimaTransform(std::string&);

	glm::mat4	ExtrapolateMatrix(AnimatedChunk part);

public:

	VoxObject(std::string filepath);
	virtual ~VoxObject(void);
	
	GLuint	&TransformID(void);
	void	Render(void);
	void	Load(void);
	void	Unload(void);
	
        void    SetTransform(glm::mat4);
        glm::mat4       GetTransform(void);
        void    SetPos(glm::vec3);
        glm::vec3       GetPos(void);
	void	Move(glm::vec3);
		
};

#endif
