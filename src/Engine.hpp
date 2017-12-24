#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>

#include "Floor.hpp"
#include "Menu.hpp"
#include "Hud.hpp"
#include "Dungeon.hpp"

enum State {
	STATE_PLAYER_TURN,
	STATE_AI_TURN,
	STATE_IN_MENU
};

class Engine {
private:
	//These are all vectors of pointers because it's unsafe to store a pointer to a member of a vector.
	std::vector<Dungeon*> Dungeons; //List of maps.
	std::vector<Menu*> menus; //List of menus.


public:
	Hud gameHud;
	State gameState;
	Dungeon* currentDungeon; //Current Dungeon
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
		Adds floor to maps.

		@param floor to be added
		@returns index
	*/
	unsigned int addDungeon(Dungeon* dungeon);

	/*
		Adds a floor and sets it to the current floor.

		@param floor to be added
		@returns index
	*/
	unsigned int addCurrentDungeon(Dungeon* dungeon);

	/*
		Gets floor at index.

		@param index of floor
		@returns pointer to floor
	*/
	Dungeon* getDungeon(unsigned int i);

	/*
		Gives index of floor pointer. (-1 is failure to find.)

		@param pointer of floor
		@returns index
	*/
	int findDungeon(Dungeon* dungeon);

	/*
		Removes floor at index.

		@param index of floor.
	*/
	void removeDungeon(unsigned int i);

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