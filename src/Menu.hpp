#pragma once
#ifndef MENU_HPP
#define MENU_HPP

#include<vector>
#include<string>
#include<tuple>

#include "Map.hpp"

class Menu {
public: //                                    v Totally super clear exactly what this means. /s (It's a pointer to a void function that takes a pointer to a Map as an argument.)
	std::vector<std::tuple<std::string, void (*)(Map*)>> options; //Duple contains text of option, and what function it calls.
	int index; //Contains which menu option is currently selected.

	Menu();

	/*
		Renders menu at (x,y)

		@param x
		@param y
	*/
	void render(int x, int y);

	/*
		Executes effect of current selection.
	*/
	void execute();

	/*
		Executes effect of target option.

		@param index of target
	*/
	void execute(int i, Map* map);

	/*
		Moves selection up.
	*/
	void selectUp();

	/*
		Moves selection down.
	*/
	void selectDown();

	/*
		Select target option.

		@param index of target.
	*/
	void select(int i);

	/*--------------------------------------------------
						EFFECTS
	--------------------------------------------------*/

	/*
		For testing purposes; spawns a player entity at (0,0)

		@param current map
	*/
	static void testOption(Map* map);
};

#endif