#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include "libtcod.hpp"

class Entity;

enum Seen {
	UNSEEN,
	SEEING,
	SEEN
};

class Tile {
public:

	virtual ~Tile() = default;

	virtual void bumped(Entity&) = 0; //Called when an entity attempts to walk onto a solid tile.
	virtual void interact(Entity&) = 0; //Called when player interacts with the tile. I guess an AI could too, but honestly I doubt that'll happen for a while.
	virtual bool isClear() = 0;
	virtual bool isOccupied() = 0;
	virtual bool isWalkable() = 0;
	virtual void render(int, int) = 0; //Called during render portion of gameplay loop.
	virtual void setSeen(Seen) = 0; //Change whether or not a tile has been seen.
	virtual void walkedOn(Entity&) = 0; //Called when an entity walks on the tile.

};

#endif