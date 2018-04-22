#pragma once

#include "Particles.hpp"
#include "bomberman.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "IState.hpp"
#include "Model.hpp"
#include "Sprite2D.hpp"
#include "bomberman.hpp"
#include "systems.hpp"
#include "components.hpp"
#include "TestParticle.hpp"

namespace c = components;

class TestState : public IState
{
	Particles _particles;
	std::vector<float> _lifetime;
	std::vector<float> _speed;



	Engine& _engine;
	Window& _window;
	Camera _camera;
	entt::DefaultRegistry _registry;
	entt::ResourceCache<Model> _modelCache;
	entt::ResourceCache<Sprite2D> _imageCache;
	systems::Collisions _cells;
public:
	TestState(Engine& engine);
	~TestState(void);
	void Update(double dt);


	void init_particles();
	void update_particles();
};
