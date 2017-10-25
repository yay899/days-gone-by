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
private:
	//These are all vectors of pointers because it's unsafe to store a pointer to a member of a vector.
	std::vector<Map*> maps; //List of maps.
	std::vector<Menu*> menus; //List of menus.

public:
	State gameState;
	Map* currentMap; //Current map.
	std::vector<Menu*> openMenus; //List of menues that are open, with index zero being the top-most menu.

	Engine();
	~Engine();

	/*
		Updates the game state
	*/
	void update();

	/*
		Renders the game to screen.
	*/
	void render();

	/*
		Adds map to maps.

		@param map to be added
		@returns index
	*/
	unsigned int addMap(Map* map);

	/*
		Adds a map and sets it to the current map.

		@param map to be added
		@returns index
	*/
	unsigned int addCurrentMap(Map* map);

	/*
		Gets map at index.

		@param index of map
		@returns pointer to map
	*/
	Map* getMap(unsigned int i);

	/*
		Gives index of map pointer. (-1 is failure to find.)

		@param pointer of map
		@returns index
	*/
	int findMap(Map* map);

	/*
		Removes map at index.

		@param index of map.
	*/
	void removeMap(unsigned int i);

	/*
		Adds menu.

		@param menu to be added
		@returns index
	*/
	unsigned int addMenu(Menu menu);

	/*
		Gets menu at index.

		@param index
		@returns pointer to menu
	*/
	Menu* getMenu(unsigned int i);

	/*
		Takes pointer to menu and finds menu with that pointer. -1 is fail to find.

		@param pointer to menu
		@returns index
	*/
	int findMenu(Menu* menu);

	/*
		Deletes menu at index.

		@param index
	*/
	void removeMenu(unsigned int i);

	/*
		Opens menu at index.

		@param index
	*/
	void openMenu(unsigned int i);

	/*
		Closes the top most menu.

		@param index
	*/
	void closeMenu();
};

#endif