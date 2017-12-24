#pragma once
#ifndef MENU_HPP
#define MENU_HPP

#include<vector>
#include<string>
#include<tuple>

#include "Floor.hpp"

class Menu {
public: //                                    v Totally super clear exactly what this means. /s (It's a pointer to a void function that takes a pointer to a Floor as an argument.)
	std::vector<std::tuple<std::string, void (*)(Floor*)>> options; //Duple contains text of option, and what function it calls.
	unsigned int index; //Contains which menu option is currently selected.
	std::string name;

	/**
		@param IDK, I can't remember
	*/
	Menu(std::string);

	/**
		Renders menu at (x,y)

		@param x
		@param y
	*/
	void render(int, int);

	/**
		Executes effect of current selection.

		@param floor of effect
	*/
	void execute(Floor*);

	/**
		Executes effect of target option.

		@param index of target
		@param floor of effect
	*/
	void execute(unsigned int , Floor*);

	/**
		Moves selection up.
	*/
	void selectUp();

	/**
		Moves selection down.
	*/
	void selectDown();

	/**
		Select target option.

		@param index of target
	*/
	void select(unsigned int);

	/*--------------------------------------------------
						EFFECTS
	--------------------------------------------------*/

	/**
		For testing purposes; spawns a player entity at (0,0)

		@param current floor
	*/
	static void debugAddPlayer(Floor*);

	/**
		For testing purposes; spawns a test enemy entitiy at the lower right corner of the floor.

		@param current floor
	*/
	static void debugAddTestEnemy(Floor*);

	/**
		For testing purposes; highlights all solid tiles.

		@param current floor
	*/
	static void debugHighlightSolid(Floor*);
};

//Constants
const TCODColor MENU_BACKGROUND = TCOD_black;
const TCODColor MENU_FOREGROUND = TCOD_white;
const TCODColor MENU_SELECT_BACKGROUND = TCOD_blue;
const TCODColor MENU_SELECT_FOREGROUND = TCOD_white;
#endif