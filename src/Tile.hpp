#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include "libtcod.hpp"

class Tile {
public:

	virtual void interact() = 0; //Called when player interacts (and/or walks on?) tile.
	virtual bool isClear() = 0;
	virtual bool isOccupied() = 0;
	virtual bool isWalkable() = 0;
	virtual void render(int, int) = 0; //Called during render portion of gameplay loop.

};

#endif