
#include "AnimatedObject.hpp"

std::istream	&operator >> (std::istream &is, AnimatedPartRaw &lhs)
{
	std::string junkInfo;
	
	is >> lhs.objectFile >> junkInfo;

	
}

AnimatedObject::AnimatedObject(std::string filepath)
{
	size_t	pathEnd = filepath.find_last_of("\\");	
	_absolutePath = filepath.substr(0, pathEnd);

	std::ifstream f(filepath);	
}

//________________

void	AnimatedObject::UsePerspective(glm::mat4 m)
{
	_perspective = m;
}

void	AnimatedObject::SetTransform(glm::mat4 m)
{
	_transform = m;
}

void	AnimatedObject::Move(glm::vec3 p)
{
	_pos += p;
}

void	AnimatedObject::MoveTo(glm::vec3 p)
{
	_pos = p;
}

glm::mat4	AnimatedObject::InterpolateMatrix(AnimatedPart part)
{
	float cycleTime = fmod(_totalTime, part.animaCycle);

	unsigned int i = 0;
	while (i < part.animaTime.size())
	{
		if (cycleTime < part.animaTime[i])
			break;
		i++;		
	}
	i--;

	float a = cycleTime - part.animaTime[i];
	float b;

	if (i != part.animaTime.size() - 1)
		b = part.animaTime[i + 1] - part.animaTime[i];
	else
		b = part.animaCycle - part.animaTime[i];

	float ratio = a / b;

	glm::mat4 x = part.animaTransform[i];
	glm::mat4 y;

	if (i != part.animaTransform.size() - 1)
		y = part.animaTransform[i + 1];
	else
		y = part.animaTransform[0];

	glm::mat4 z = y - x;

	return x + z * ratio;
}

void	AnimatedObject::Render(void)
{
	_time.Fix();

	for (unsigned i = 0; i < _parts.size(); i++)
	{
		glm::mat4 matrix = InterpolateMatrix(_parts[i]);
		glm::mat4 translate1 = glm::translate(_parts[i].partPos);
		glm::mat4 translate2 = glm::translate(_pos);

		matrix = translate2 * _transform * translate1 *	matrix;
		_parts[i].object->SetTransform(matrix);
		_parts[i].object->UsePerspective(_perspective);
		_parts[i].object->Render();
	}
	_totalTime += _time.GetDeltaTime();
}
