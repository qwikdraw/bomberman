
#include "AnimatedObject.hpp"

std::istream	&operator >> (std::istream &is, AnimatedObject::AnimatedPartRaw &lhs)
{
	std::string junkInfo;
	
	is >> lhs.objectFile >> lhs.textureFile >> junkInfo;

	if (!is)
		throw std::exception();
	
	std::string s;
	while (1)
	{
		s = "";
		is >> s;
		if (s != "matrix")
			break;
		
		glm::mat4 matrix;		
		for (int i = 0; i < 16; i++)
			is >> matrix[i / 4][i % 4];
		lhs.transform.push_back(matrix);
		
		float t;
		is >> t;
		lhs.time.push_back(t);
	}
	is >> lhs.cycle >> junkInfo >> lhs.pos[0] >> lhs.pos[1] >> lhs.pos[2];	
	return is;
}

AnimatedObject::AnimatedObject(std::string filepath)
{
	size_t	pathEnd = filepath.find_last_of("/");	
	std::string absolutePath = filepath.substr(0, pathEnd);

	std::ifstream f(filepath);
	
	while (f)
	{
		AnimatedPartRaw raw;
		try
		{
			f >> raw;
		}
		catch (std::exception)
		{
			break;
		}
	
		AnimatedPart processed;

		processed.animaTransform = raw.transform;
		processed.animaTime = raw.time;
		processed.animaCycle = raw.cycle;
		processed.partPos = raw.pos;
		processed.object = new ObjFileObject(absolutePath + "/" + raw.objectFile,
						     absolutePath + "/" + raw.textureFile);

		_parts.push_back(processed);
	}
	_pos = glm::vec3(0, 0, 0);
	_transform = glm::mat4(1);

}

AnimatedObject::~AnimatedObject(void)
{
	for (auto part : _parts)
		delete part.object;
}

//________________

void	AnimatedObject::UseExplicitPerspective(std::pair<glm::mat4, glm::mat4> p)
{
	_explicitPerspective = p;
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
		_parts[i].object->UseExplicitPerspective(_explicitPerspective);
		_parts[i].object->Render();
	}
	_totalTime += _time.GetDeltaTime();
}
