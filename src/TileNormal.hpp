#pragma once
#ifndef TILE_NORMAL_HPP
#define TILE_NORMAL_HPP

#include "Tile.hpp"

class TileNormal : public Tile {
protected:

	char character;
	bool clear;
	bool occupied;
	bool walkable;

public:

	TileNormal(char, bool, bool, bool);

	/*
		Does nothing.
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
		@return walkable && !occupied 
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