#include "LevelSelectState.hpp"
#include "components.hpp"
#include "MenuState.hpp"
#include "systems.hpp"
#include "save.hpp"

namespace c = components;

static const glm::vec2 botlefts[8] = {{-0.78, 0.1},
				      {-0.38, 0.1},
				      {0.02, 0.1},
				      {0.42, 0.1},
				      {-0.78, -0.6},
				      {-0.38, -0.6},
				      {0.02, -0.6},
				      {0.42, -0.6}
};

static const glm::vec2 toprights[8] = {{-0.42, 0.6},
				       {-0.02, 0.6},
				       {0.38, 0.6},
				       {0.78, 0.6},
				       {-0.42, -0.1},
				       {-0.02, -0.1},
				       {0.38, -0.1},
				       {0.78, -0.1}
};
	
static void	create_level_button(entt::DefaultRegistry& r, Engine& engine, size_t i)
{
	std::string level = "0X";
	level[1] = i + '1';
	
	auto button = r.create();
	auto event = [&engine, level](entt::DefaultRegistry& r, uint32_t e)
	{
		engine.ChangeState(new GameState(engine, level));
	};
	r.assign<c::Button>(button,
			    event,
			    botlefts[i],
			    toprights[i]);
	r.assign<c::Image>(button,
			   "assets/textures/blue_button.png",
			   botlefts[i],
			   toprights[i],
			   1);
	r.assign<c::Text>(button,
			  level,
			  botlefts[i] + 0.1 * (toprights[i] - botlefts[i]),
			  toprights[i] - 0.1 * (toprights[i] - botlefts[i]));
}

static void	create_locked_icon(entt::DefaultRegistry& r, size_t i)
{
	std::string level = "0X";
	level[1] = i + '1';

	auto locked = r.create();
	r.assign<c::Image>(locked,
			   "assets/textures/locked.png",
			   botlefts[i],
			   toprights[i],
			   1);
}

LevelSelectState::LevelSelectState(Engine& e) :
_engine(e), _window(e.window)
{
	std::string level = save::getLevel();
	size_t levels_unlocked = level[1] - '0';

	for (size_t i = 0; i < 8; i++)
	{
		if (i < levels_unlocked)
			create_level_button(_registry, _engine, i);
		else
			create_locked_icon(_registry, i);
	}
	auto background = _registry.create();
	_registry.assign<c::Image>(background, "assets/textures/rock.png");
	
}

LevelSelectState::~LevelSelectState(void) {}

void	LevelSelectState::Update(double dt)
{
	systems::Buttons(_registry, _window);
	systems::Images(_registry, _imageCache, _window);
	systems::Texts(_registry, _window);
}

