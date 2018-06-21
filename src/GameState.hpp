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
#include "Cells.hpp"
#include "Effects.hpp"
#include "LoreDisplay.hpp"

namespace c = components;

//! Game State class. Implements IState
/*! 
 * The main game play. Each level (1-8) is its own game state class. Saves the current level. 
*/

class GameState : public IState
{
	Engine& _engine;
	Window& _window;
	Camera _camera;
	i::ISound *_music;
	entt::DefaultRegistry _registry;
	entt::ResourceCache<Model> _modelCache;
	entt::ResourceCache<Sprite2D> _imageCache;
	systems::Cells _cells;
	LoreDisplay _lorePannel;
	
public:
	GameState(Engine& engine, std::string level);

	~GameState(void);

	//! Updates models, buttons, images, lighting, and other misc systems per frame.
	void Update(double dt);
};
