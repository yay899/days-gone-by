#pragma once
#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "libtcod.hpp"
#include "Tile.hpp"
#include "Entity.hpp"

class Map {
protected:
	
	int w, h;
	Tile** tileMap; //Map of tiles.
	std::vector<Entity*> entities; //All entities in map.

public:

	Map(int w, int h);
	~Map();

	/*
		Updates all entities in map.

		@parem time
		@parem keycode
	*/
	void update(float t, TCOD_keycode_t key);

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
		Helper function; sets tiles on rectangle to provided tile.

		@parem x
		@parem y
		@parem width
		@parem height
		@parem outline tile
	*/
	void setRectangle(int x, int y, int width, int height, Tile outline);

	/*
		Helper function; sets tiles on rectangle to provided tile, and fill to other provided tile.

		@parem x
		@parem y
		@parem width
		@parem height
		@parem outline tile
		@parem fill tile
	*/
	void setRectangle(int x, int y, int width, int height, Tile outline, Tile fill);

	/*
		Helper function; checks if tile on map is solid.

		@parem x
		@parem y
		@return solidity of tile at (x,y)
	*/
	bool isSolid(int x, int y);

	/*
		@return width of map
	*/
	int getWidth();

	/*
		@return height of map
	*/
	int getHeight();
};

#endif