#include "SettingState.hpp"
#include "components.hpp"
#include "MenuState.hpp"
#include "systems.hpp"

namespace c = components;

static int	keyFromAction(c::ActionType action, Engine& engine)
{
	switch (action)
	{
	case (c::BOMB_ACTION):
		return engine.keyBind.bomb;
	case (c::UP_ACTION):
		return engine.keyBind.up;
	case (c::LEFT_ACTION):
		return engine.keyBind.left;
	case (c::RIGHT_ACTION):
		return engine.keyBind.right;
	case (c::DOWN_ACTION):
		return engine.keyBind.down;
	}
	return 0;
}

static std::string	keyToString(int key)
{
	std::string out;

        if (key == ' ')
                out += "space";
        else if (key == GLFW_KEY_RIGHT)
                out += "right arrow";
        else if (key == GLFW_KEY_LEFT)
                out += "left arrow";
        else if (key == GLFW_KEY_UP)
                out += "up arrow";
        else if (key == GLFW_KEY_DOWN)
                out += "down arrow";
        else
                out += (char)key;
	
	return out;
}

static void	keybind_button(entt::DefaultRegistry& r,
			       glm::vec2 botleft,
			       glm::vec2 topright,
			       std::string imagePath,
			       c::ActionType action,
			       Engine& engine)
{
	auto bind = r.create();
	auto event = [action](entt::DefaultRegistry& r, uint32_t e)
	{
		auto &text = r.get<c::Text>(e);
		text.words = "press a key";
		if (!r.has<c::KeyBind>(e))
			r.assign<c::KeyBind>(e, action);
	};
	r.assign<c::Button>(bind, event, botleft, topright);
	r.assign<c::Image>(bind, imagePath, botleft, topright, 1);	
	r.assign<c::Text>(bind,
			  keyToString(keyFromAction(action, engine)),
			  botleft + 0.1 * (topright - botleft),
			  topright - 0.1 * (topright - botleft));
}

static void	resolution_button(entt::DefaultRegistry& r,
				  glm::vec2 botleft,
				  glm::vec2 topright,
				  std::string imagePath,
				  int width,
				  int height,
				  bool fullscreen,
				  Window& window,
				  std::string text)
{
	auto reso = r.create();
	auto event = [&window, width, height, fullscreen](entt::DefaultRegistry& r, uint32_t e)
	{
		const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		int MinW = std::min(width, mode->width);
		int MinH = std::min(height, mode->height);

		if (MinW * 9 > MinH * 16)
			MinW = MinH * 16 / 9;
		else
			MinH = MinW * 9 / 16;
		
		if (fullscreen)
		{
			glfwSetWindowMonitor(window.GetGLWindow(),
					     glfwGetPrimaryMonitor(),
					     0, 0, MinW, MinH, mode->refreshRate);
		}
		else
			glfwSetWindowMonitor(window.GetGLWindow(), NULL,
					     0, 0, MinW, MinH, GLFW_DONT_CARE);
	};
	r.assign<c::Button>(reso, event, botleft, topright);
	r.assign<c::Image>(reso, imagePath, botleft, topright, 1);
	r.assign<c::Text>(reso,
			  text,
			  botleft + 0.1 * (topright - botleft),
			  topright - 0.1 * (topright - botleft));
}


static void	sound_button(entt::DefaultRegistry& r,
				  glm::vec2 botleft,
				  glm::vec2 topright,
				  i::ISoundEngine& sound)
{
	std::string text;
	std::string imagePath;
	auto s = r.create();
	int	volume = sound.getSoundVolume();

	text = volume ? "On" : "Off"; 
	imagePath = volume ? "assets/textures/blue_button.png" :
		"assets/textures/dark_blue_button.png";
	auto event = [&sound](entt::DefaultRegistry& r, uint32_t e)
	{
		int	vol = sound.getSoundVolume();
		auto &text = r.get<c::Text>(e);
		auto &image = r.get<c::Image>(e);
		if (vol)
		{
			image.name = "assets/textures/dark_blue_button.png";
			text.words = "Off";
			sound.setSoundVolume(0);
		}
		else
		{
			image.name = "assets/textures/blue_button.png";
			text.words = "On";
			sound.setSoundVolume(1);
		}
	};
	r.assign<c::Button>(s, event, botleft, topright);
	r.assign<c::Image>(s, imagePath, botleft, topright, 1);
	r.assign<c::Text>(s,
			  text,
			  botleft + 0.1 * (topright - botleft),
			  topright - 0.1 * (topright - botleft));
}

SettingState::SettingState(Engine& e) :
_engine(e), _window(e.window)
{

//create the settings backdrop

	auto settingMenu = _registry.create();
	_registry.assign<c::Image>(settingMenu, "assets/textures/setting_menu.png");
	
//creating a button to go back to menu
	
	auto menuButton = _registry.create();
	auto gotoMenu = [this](entt::DefaultRegistry& r, uint32_t e)
	{
		_engine.PopState();
	};
	_registry.assign<c::Button>(menuButton,
				    gotoMenu,
				    glm::vec2(-0.7, -0.8),
				    glm::vec2(-0.25, -0.6));
	_registry.assign<c::Image>(menuButton,
				   "assets/textures/blue_button.png",
				   glm::vec2(-0.7, -0.8),
				   glm::vec2(-0.25, -0.6),
				   1);
	_registry.assign<c::Text>(menuButton,
				  "BACK",
				  glm::vec2(-0.65, -0.76),
				  glm::vec2(-0.3, -0.64));

//creating a keybind buttons

	keybind_button(_registry,
		       glm::vec2(-0.6, 0.5),
		       glm::vec2(-0.4, 0.6),
		       "assets/textures/blue_button.png",
		       c::BOMB_ACTION,
		       _engine);
	keybind_button(_registry,
		       glm::vec2(-0.6, 0.33),
		       glm::vec2(-0.4, 0.43),
		       "assets/textures/blue_button.png",
		       c::UP_ACTION,
		       _engine);
	keybind_button(_registry,
		       glm::vec2(-0.6, 0.135),
		       glm::vec2(-0.4, 0.235),
		       "assets/textures/blue_button.png",
		       c::DOWN_ACTION,
		       _engine);
	keybind_button(_registry,
		       glm::vec2(-0.6, -0.05),
		       glm::vec2(-0.4, 0.05),
		       "assets/textures/blue_button.png",
		       c::LEFT_ACTION,
		       _engine);
	keybind_button(_registry,
		       glm::vec2(-0.6, -0.24),
		       glm::vec2(-0.4, -0.14),
		       "assets/textures/blue_button.png",
		       c::RIGHT_ACTION,
		       _engine);

//create resolution buttons

	resolution_button(_registry,
                          glm::vec2(0.1, 0.4),
                          glm::vec2(0.35, 0.55),
                          "assets/textures/blue_button.png",
                          1200,
                          675,
                          false,
                          _window,
                          "1200 X 675");
	
	resolution_button(_registry,
			  glm::vec2(0.1, 0.2),
			  glm::vec2(0.35, 0.35),
			  "assets/textures/blue_button.png",
			  1600,
			  900,
			  false,
			  _window,
			  "1600 X 900");

        resolution_button(_registry,
                          glm::vec2(0.55, 0.4),
                          glm::vec2(0.8, 0.55),
                          "assets/textures/blue_button.png",
                          2400,
                          1350,
                          false,
                          _window,
			  "2400 X 1350");

	resolution_button(_registry,
                          glm::vec2(0.55, 0.2),
                          glm::vec2(0.8, 0.35),
                          "assets/textures/blue_button.png",
                          4000,
                          2250,
                          false,
                          _window,
                          "4000 X 2250");
	
	resolution_button(_registry,
                          glm::vec2(0.3, -0.02),
                          glm::vec2(0.6, 0.12),
                          "assets/textures/blue_button.png",
                          100000,
                          100000,
                          true,
                          _window,
			  "Fullscreen");

//create sound button

	sound_button(_registry,
                          glm::vec2(0.35, -0.7),
                          glm::vec2(0.55, -0.6),
                          _engine.sound);
}

SettingState::~SettingState(void) {}

void	SettingState::Update(double dt)
{
	systems::BindCheck(_registry, _window, _engine);
	systems::Buttons(_registry, _window);
	systems::Images(_registry, _imageCache, _window);
	systems::Texts(_registry, _window);
}
