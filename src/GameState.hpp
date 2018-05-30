#pragma once

#include "bomberman.hpp"
#include "IState.hpp"
#include "systems.hpp"
#include "components.hpp"
#include "Particles.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Model.hpp"
#include "Sprite2D.hpp"
#include "TestParticle.hpp"
#include "Cells.hpp"
#include "Effects.hpp"

namespace c = components;

class GameState : public IState
{
	Engine& _engine;
	Window& _window;
	Camera _camera;
	entt::DefaultRegistry _registry;
	entt::ResourceCache<Model> _modelCache;
	entt::ResourceCache<Sprite2D> _imageCache;
	systems::Cells _cells;
	ISoundEngine *_sound;
	
public:
	GameState(Engine& engine, std::string level);
	~GameState(void);
	void Update(double dt);
};
