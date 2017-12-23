#pragma once
#ifndef TILE_NORMAL_HPP
#define TILE_NORMAL_HPP

#include "Tile.hpp"

class Tile;
class Entity;

class TileNormal : public Tile {
protected:

	TCODColor backgroundColor;
	char character;
	bool clear;
	TCODColor foregroundColor;
	bool occupied;
	bool walkable;

public:

	TileNormal();

	/*
		@param character
		@param foregroundColor
		@param backgroundColor
		@param clear
		@param occupied
		@param walkable
	*/
	TileNormal(char, TCODColor, TCODColor, bool, bool, bool);

	/*
		Does nothing.
	*/
	void bumped(Entity&);

	/*
		Does nothing.
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
		@return walkable && !occupied 
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