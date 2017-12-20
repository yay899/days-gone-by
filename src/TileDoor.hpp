#pragma once
#ifndef TILE_DOOR_HPP
#define TILE_DOOR_HPP

#include "Tile.hpp"

class TileDoor : public Tile {
protected:

	bool clear;
	char closedCharacter;
	bool occupied;
	bool open;
	char openCharacter;
	bool walkable;

public:

	/*
		@param open character
		@param closed character
		@param clear
		@param occupied
		@param walkable
		@param open
	*/
	TileDoor(char, char, bool, bool, bool, bool);

	/*
		Opens door.
	*/
	void bumped(Entity&);

	/*
		Toggles door.
	*/
	void interact(Entity&);

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

	/*
		Does nothing.
	*/
	void walkedOn(Entity&);

};

#endif