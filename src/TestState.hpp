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
	Engine& _engine;
	Window& _window;
	Camera _camera;
	entt::DefaultRegistry _registry;
	entt::ResourceCache<Model> _modelCache;
	entt::ResourceCache<Sprite2D> _imageCache;
	systems::Cells _cellQuery;

	ParticleExplosion *_explosion;
	
public:
	TestState(Engine& engine);
	~TestState(void);
	void Update(double dt);
};
