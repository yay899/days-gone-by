#pragma once
#ifndef TILE_DOOR_HPP
#define TILE_DOOR_HPP

#include "Tile.hpp"

class TileDoor : public Tile {
protected:

	bool clear;
	TCODColor closedBackgroundColor;
	char closedCharacter;
	TCODColor closedForegroundColor;
	bool occupied;
	TCODColor openBackgroundColor;
	bool open;
	TCODColor openForegroundColor;
	char openCharacter;
	bool walkable;

public:

	/*
		@param open character
		@param open foreground color
		@param open background color
		@param closed character
		@param closed foreground color
		@param closed background color
		@param clear
		@param occupied
		@param walkable
		@param open
	*/
	TileDoor(char, TCODColor, TCODColor, char, TCODColor, TCODColor, bool, bool, bool, bool);

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