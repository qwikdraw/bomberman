#ifndef ANIMATEDOBJECT_HPP
#define ANIMATEDOBJECT_HPP

class	AnimatedObject
{
	struct	AnimatedPartRaw
	{
		std::string objectFile;
		
	        std::istream    &operator >> (std::istream &is, AnimatedPart &lhs);
	};
	
	struct	AnimatedPart
	{
		ObjFileObject *object;
		std::vector<glm::mat4> animaTransform;
		std::vector<float> animaTime;
		float animaCycle;
		glm::vec3 partPos;
	};

private:

	Time _time;
	std::vector<AnimatedPart> _parts;
	float _totalTime;
	GLuint _transformID;
	glm::vec3 _pos;
	glm::mat4 _transform;
	std::string _absolutePath;

	
	glm::mat4	InterpolateMatrix(AnimatedPart part);

public:

	AnimatedObject(std::string filepath);

	void	UsePerspective(glm::mat4);
	void	SetTransform(glm::mat4);
	void	Move(glm::vec3);
	void	MoveTo(glm::vec3);
	
	void	Render(void);
};

#endif
