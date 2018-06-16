#include "GameState.hpp"
#include "ParticleExplosion.hpp"
#include "build_level.hpp"
#include "PauseState.hpp"
#include "save.hpp"

static void	generate_ui(entt::DefaultRegistry& reg, Engine& engine, std::string level)
{
// generate text for speed
	auto speedText = reg.create();
	auto speedUpdate = [](entt::DefaultRegistry& r, uint32_t e)
	{
		float& time = r.get<c::TimedEffect>(e).timeLeft;
		time += 0.2;

		if (!r.has<c::Player>())
			return;
		
		float playerSpeed = r.get<c::Player>().speed;
		std::string& words = r.get<c::Text>(e).words;
		std::stringstream ss;
		ss << std::fixed << std::setprecision(1) << playerSpeed;
		words = ss.str();
	};
	reg.assign<c::Text>(speedText,
			    "",
			    glm::vec2(0.42, -0.945),
			    glm::vec2(0.72, -0.845));
	reg.assign<c::TimedEffect>(speedText, 0.0f, speedUpdate);

// generate text for bomb power
	auto bombText = reg.create();
	auto bombUpdate = [](entt::DefaultRegistry& r, uint32_t e)
	{
		float& time = r.get<c::TimedEffect>(e).timeLeft;
		time += 0.2;

		if (!r.has<c::Player>())
			return;

		float power = r.get<c::Player>().bombPower;
		std::string& words = r.get<c::Text>(e).words;
		std::stringstream ss;
		ss << std::fixed << std::setprecision(0) << power;
		words = ss.str();
	};
	reg.assign<c::Text>(bombText,
			    "",
			    glm::vec2(-0.415, -0.945),
			    glm::vec2(-0.315, -0.845));
	reg.assign<c::TimedEffect>(bombText, 0.0f, bombUpdate);

// create current level text
	auto levelText = reg.create();
	reg.assign<c::Text>(levelText,
			    level,
			    glm::vec2(-0.05, 0.835),
			    glm::vec2(0.15, 0.965));
	
// create ui texture
	auto UI = reg.create();
	reg.assign<c::Image>(UI, "assets/textures/UI.png");
}

GameState::GameState(Engine& e, std::string level) :
_engine(e), _window(e.window)
{
	_engine.sound.stopAllSounds();
	_camera.Move(glm::vec3(0, -10, 20));
	_camera.Rotate(glm::vec3(0, 0, 1), 90);
	_camera.Rotate(glm::vec3(0, 1, 0), 64);

	build_level(_registry, _engine, level, &_music);
	_modelCache.load<systems::ModelLoader>(entt::HashedString("bomb"), ASSET_PATH "bomb.model");
	glClearColor(0.2, 0.25, 0.29, 1.0);

	if (level == "01" || level == "01")
	{
		auto sparkles = _registry.create();
		_registry.assign<c::Position>(sparkles, glm::vec3(0, 0, 0));
		_registry.assign<c::TimedEffect>(sparkles, 100000.0f, scripts::destroy());
		_registry.assign<c::Particles>(sparkles, Effects::sparkles, 100000.0f);
	}

	generate_ui(_registry, _engine, level);
	save::updateLevel(level);
}

GameState::~GameState(void) {}

void GameState::Update(double dt)
{
	if (_music && _music->getIsPaused())
		_music->setIsPaused(false);
	if (_window.Key(GLFW_KEY_ESCAPE))
	{
		if (_music)
			_music->setIsPaused(true);
		_engine.PushState(new PauseState(_engine));
	}
	_cells(_registry);
	
	systems::RenderModels(_registry, _modelCache, _window, _camera, dt);
	systems::TimedEffect(_registry, dt);
	systems::Buttons(_registry, _window);
	systems::Images(_registry, _imageCache, _window);
	systems::Player(_registry, _window, _engine.keyBind, _cells, _camera, dt);
	systems::Velocity(_registry, _cells, dt);
	systems::RenderParticles(_registry, _camera);
	systems::Danger(_registry, _cells);
	systems::Explosion(_registry, _cells);
	systems::AI(_registry, _window, dt);
	systems::Lighting(_registry, dt);
	systems::Images(_registry, _imageCache, _window);
	systems::Texts(_registry, _window);
	systems::Sound(_registry, dt);
}
