#pragma once

#include "bomberman.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "IState.hpp"
#include "Model.hpp"
#include <entt/entt.hpp>

class TestState : public IState
{
	Engine& _engine;
	Window& _window;
	Camera _camera;
	std::vector<Light*> _lights;
	entt::DefaultRegistry _registry;
	entt::ResourceCache<Model> _cache;
public:
	TestState(Engine& engine);
	~TestState(void);
	void Update(double dt);
};
