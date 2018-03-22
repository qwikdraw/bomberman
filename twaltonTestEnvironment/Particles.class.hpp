#ifndef PARTICLES_CLASS_HPP
#define PARTICLES_CLASS_HPP

class Particles
{
public:
	struct ParticleProperty
	{
		glm::vec3 pos;
		glm::vec4 color;
		glm::vec3 velocity;
		float size;
	};

private:

	std::vector<ParticleProperty> _particles;

	std::vector<float> _vertices;
	std::vector<float> ;
	
public:
	
	Particles(int amount);

	void	ApplyFunction(std::function<void(std::vector<ParticleProperty>&)> f);
	void	ApplyFunction(std::function<void(void*, std::vector<ParticleProperty>&)> f);
	void	Draw(void);
};

#endif
