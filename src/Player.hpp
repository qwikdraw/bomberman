#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Controled.hpp"
#include "Window.hpp"
#include "AnimatedObject.hpp"

#define PLAYER_MODEL "src/animationFile"

class	Player
{
private:

	Controled _position;
	Window	&_window;
	AnimatedObject _model;
	
public:

	Player(Window&);

	glm::vec3	Position(void);

	void	Update(float dt);
	void	Render(std::pair<glm::mat4, glm::mat4> perspective);
};

#endif
