
#include "Light.hpp"

std::vector<glm::vec3> Light::_positions;
std::vector<glm::vec3> Light::_colors;
std::vector<float> Light::_falloffs;

const std::vector<glm::vec3> &Light::positions = Light::_positions;
const std::vector<glm::vec3> &Light::colors = Light::_colors;
const std::vector<float> &Light::falloffs = Light::_falloffs;


Light::Light(glm::vec3 pos, glm::vec3 color, float falloff) :
_pos(pos),
_color(color),
_falloff(falloff)
{
	_positions.push_back(_pos);
	_colors.push_back(_color);
	_falloffs.push_back(_falloff);
}

Light::~Light(void)
{
	for (size_t i = 0; i < _positions.size(); i++)
	{
		if (_pos == _positions[i] && _color == _colors[i] && _falloff == _falloffs[i])
		{
			_positions.erase(_positions.begin() + i);
			_colors.erase(_colors.begin() + i);
			_falloffs.erase(_falloffs.begin() + i);
			break;
		}
	}
}
