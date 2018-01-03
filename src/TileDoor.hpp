#pragma once
#ifndef TILE_DOOR_HPP
#define TILE_DOOR_HPP

#include "Tile.hpp"

class Tile;
class Entity;

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
	Seen seen; //TODO Make door save the last time you saw it.
	bool walkable;

public:

	/**
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

	/**
		Opens door.

		@param entity that bumped
	*/
	void bumped(Entity&);

	/**
		Toggles door.

		@param entity that interacted
	*/
	void interact(Entity&);

	/**
		@return clear
	*/
	bool isClear();

	/**
		@return occupied
	*/
	bool isOccupied();

	/**
		@return walkable && !occupied && open
	*/
	bool isWalkable();

	/**
		Sets tile on TCODConsole::root.

		@param row
		@param column
	*/
	void render(int, int);
	
	/**
		Sets Seen state of tile.
		
		@param state
	*/
	void setSeen(Seen);

	/**
		Does nothing.

		@param entity that walked
	*/
	void walkedOn(Entity&);

};

#endif