
#include "Player.hpp"

Player::Player(Window &window) : _position(window, 4),
				 _window(window),
				 _model(PLAYER_MODEL)
{
	(void)_window;
}

glm::vec3	Player::Position(void)
{
	return _position.Position();
}

void	Player::Update(float dt)
{
	_position.Update(dt);
}

void	Player::Render(std::pair<glm::mat4, glm::mat4> perspective)
{
	_model.UsePerspective(perspective);
	_model.MoveTo(_position.Position());
	_model.Render();
}
