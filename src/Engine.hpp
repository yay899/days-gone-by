#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>

#include "Map.hpp"
#include "Menu.hpp"

enum State {
	STATE_PLAYER_TURN,
	STATE_AI_TURN,
	STATE_IN_MENU
};

class Engine {
public:
	State gameState;
	//These are all vectors of pointers because it's unsafe to store a pointer to a member of a vector.
	std::vector<Map*> maps; //List of maps.
	Map* currentMap; //Current map.
	std::vector<Menu*> menus; //List of menus.
	std::vector<Menu*> openMenus; //List of menues that are open, with index zero being the top-most menu.

	Engine();
	~Engine();

	/*
		Updates the game state
	*/
	void update(Map* map);

	/*
		Renders the game to screen.
	*/
	void render(Map* map);
};

#endif