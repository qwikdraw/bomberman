#include "Sparkles.hpp"

Sparkles::Sparkles(float width, float height) : _particles(Particles(width * height * 3))
{
	_amount = width * height * 3;
	_colors.resize(_amount);
	_startPos.resize(_amount);

	for (auto &p : _startPos)
		p = glm::linearRand(glm::vec3(-width/2, -height/2, 0), glm::vec3(width/2, height/2, 1));

	glm::vec3 col2(0.4, 0.6, 0.85);
	glm::vec3 col1(0.8, 0.9, 1);

	for (auto &col : _colors)
		col = glm::linearRand(col1, col2);
}

void	Sparkles::Render(std::pair<glm::mat4, glm::mat4> perspective,
			   glm::vec3,
			   float time)
{
	time /= 5;
	time = fmod(time, 1);
	_particles.UseExplicitPerspective(perspective);

	auto &physicalAttrib = _particles.GetPhysicalAttributes();
	auto &colorAttrib = _particles.GetColorAttributes();

	for (size_t i = 0; i < physicalAttrib.size(); i += 4)
	{
		glm::vec3 pos = _startPos[i / 4];
		pos.z += time;
		pos.z = fmod(pos.z, 1);

		physicalAttrib[i] = pos.x;
		physicalAttrib[i + 1] = pos.y;
		physicalAttrib[i + 2] = pos.z;
		physicalAttrib[i + 3] = 0.05 - pos.z * 0.05;
	}
	for (size_t i = 0; i < colorAttrib.size(); i += 4)
	{
		glm::vec3 col = _colors[i / 4] * (physicalAttrib[i + 2]);

		colorAttrib[i] = col.x;
		colorAttrib[i + 1] = col.y;
		colorAttrib[i + 2] = col.z;
		colorAttrib[i + 3] = 1;
	}
	_particles.Update();
	_particles.Render();
}
