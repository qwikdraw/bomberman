#pragma once

#include <entt/entt.hpp>
#include "Camera.hpp"
#include "Light.hpp"
#include "IState.hpp"
#include "Model.hpp"
#include "Sprite2D.hpp"
#include "bomberman.hpp"
#include "systems.hpp"
#include "components.hpp"

namespace c = components;

class TestState : public IState
{
	Engine& _engine;
	Window& _window;
	Camera _camera;
	std::vector<Light*> _lights;
	entt::DefaultRegistry _registry;
	entt::ResourceCache<Model> _modelCache;
	entt::ResourceCache<Sprite2D> _imageCache;
	systems::Collisions _cells;
public:
	TestState(Engine& engine);
	~TestState(void);
	void Update(double dt);
};
