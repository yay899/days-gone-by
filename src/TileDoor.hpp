#pragma once
#ifndef TILE_DOOR_HPP
#define TILE_DOOR_HPP

#include "Tile.hpp"

class TileDoor : public Tile {
protected:

	char character;
	bool clear;
	bool occupied;
	bool open;
	bool walkable;

public:

	TileDoor(char, bool, bool, bool, bool);

	/*
		Toggles door.
	*/
	void interact();

	/*
		@return clear
	*/
	bool isClear();

	/*
		@return occupied
	*/
	bool isOccupied();

	/*
		@return walkable && !occupied && open
	*/
	bool isWalkable();

	/*
		Sets tile on TCODConsole::root.

		@param row
		@param column
	*/
	void render(int, int);

};

#endif