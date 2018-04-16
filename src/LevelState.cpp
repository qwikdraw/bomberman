
#include "LevelState.hpp"

LevelState::LevelState(Window &window, std::string levelFile) : _map(levelFile),
								_player(window)
{
	(void)levelFile;
	(void)window;
	_camera.Rotate(glm::vec3(0, 0, 1), 90);
	_camera.MoveTo(glm::vec3(-10, 0, 10));
	_camera.Rotate(glm::vec3(0, 1, 0), 45);
}

void	LevelState::Update(Engine *game, Window &window, double dt)
{
	(void)game;
	(void)window;
	_player.Update(dt);
}

void	LevelState::Draw(Engine *game, Window &window, double dt)
{
	(void)game;
	(void)window;
	(void)dt;
	Light light(glm::vec3(0, 0, 10), glm::vec3(1, 1, 1), 100);
	_player.Render(_camera.Perspective());
	_map.Render(_camera.Perspective());
}
