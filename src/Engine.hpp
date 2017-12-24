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

	/**
		Updates the game state
	*/
	void update();

	/**
		Renders the game to screen.
	*/
	void render();

	/**
		Adds floor to maps.

		@param floor to be added
		@return index
	*/
	unsigned int addDungeon(Dungeon*);

	/**
		Adds a floor and sets it to the current floor.

		@param floor to be added
		@return index
	*/
	unsigned int addCurrentDungeon(Dungeon*);

	/**
		Gets floor at index.

		@param index of floor
		@return pointer to floor
	*/
	Dungeon* getDungeon(unsigned int);

	/**
		Gives index of floor pointer. (-1 is failure to find.)

		@param pointer of floor
		@return index
	*/
	unsigned int findDungeon(Dungeon*);

	/**
		Removes floor at index.

		@param index of floor.
	*/
	void removeDungeon(unsigned int);

	/**
		Adds menu.

		@param menu to be added
		@return index
	*/
	unsigned int addMenu(Menu);

	/**
		Gets menu at index.

		@param index
		@return pointer to menu
	*/
	Menu* getMenu(unsigned int);

	/**
		Takes pointer to menu and finds menu with that pointer. (-1 is fail to find.)

		@param pointer to menu
		@return index
	*/
	int findMenu(Menu*);

	/**
		Deletes menu at index.

		@param index
	*/
	void removeMenu(unsigned int);

	/**
		Opens menu at index.

		@param index
	*/
	void openMenu(unsigned int);

	/**
		Closes the top most menu.

		@param index
	*/
	void closeMenu();
};

#endif