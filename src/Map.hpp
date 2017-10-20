#pragma once
#ifndef MAP_H
#define MAP_H

#include <vector>

#include "libtcod.hpp"
#include "Tile.hpp"

class Map {
public:
	
	int w, h;
	Tile** tileMap; //Map of tiles.
	//std:::vector<Entity> entities; //Uncomment when implimented.

	Map(int w, int h);
	~Map();

	/*
		Displays the contents of the map on TCODConsole->root.
	*/
	void render();

	/*
		Fills the map with the specified tiles.
	*/
	void generateFill(Tile t);

	//TODO write more generators.

	/*
		Helper function; gets pointer to tile at (x,y).

		@parem x
		@parem y
		@return pointer to tile
	*/
	Tile* getTilePointer(int x, int y);

	/*
		Helper function; gets tile info at (x,y).

		@parem x
		@parem y
		@return tile info
	*/
	Tile getTile(int x, int y);

	/*
		Helper function; sets tile at (x,y) to provided tile.

		@parem x
		@parem y
		@parem desired tile
	*/
	void setTile(int x, int y, Tile t);

	/*
		Helper function; checks if tile on map is solid.

		@parem x
		@parem y
		@return solidity of tile at (x,y)
	*/
	bool isSolid(int x, int y);
};

#endif