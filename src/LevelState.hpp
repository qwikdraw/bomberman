#ifndef LEVELSTATE_HPP
#define LEVELSTATE_HPP

#include "IState.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include "Map.hpp"

class	LevelState : public IState
{
private:

	Map _map;
	Player _player;
	Camera _camera;
	
public:

	LevelState(Window&, std::string levelFile);
	
	void	Update(Engine*, Window&, double dt);
	void	Draw(Engine*, Window&, double dt);
};

#endif
