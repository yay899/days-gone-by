#pragma once
#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "libtcod.hpp"
#include "TileLegacy.hpp"
#include "Entity.hpp"

//Need to declare this here due to cyclical #includes.
class Entity;
class TileLegacy;

class Map {
protected:

	unsigned int w, h;
	TileLegacy*** tileMap; //Map of tiles.

public:
	std::vector<Entity*> entities; //All entities in map.
	std::vector<Entity*> teamPlayer; //ONLY player entities.
	std::vector<Entity*> teamAI; //Everything else.

	Map(unsigned int w, unsigned int h);
	~Map();

	/*
		Updates all entities in map.

		@param time
		@param keycode
	*/
	void update();

	/*
		Displays the contents of the map on TCODConsole->root.
	*/
	void render();

	/*
		Fills the map with the specified tiles.
	*/

	/*
		Helper function; add entity to teamPlayer and entities.

		@param pointer to new entity
	*/
	void addTeamPlayer(Entity* e);

	/*
		Helper function; add entity to teamAI and entities

		@param pointer to new entity
	*/
	void addTeamAI(Entity* e);

	/*
		Fills map with a single tile

		@param desired tile
	*/
	void generateFill(TileLegacy* t);

	//TODO write more generators.

	/*
		Helper function; gets pointer to tile at (x,y).

		@param x
		@param y
		@return pointer to tile
	*/
	TileLegacy* getTilePointer(unsigned int x, unsigned int y);

	/*
		Helper function; gets tile info at (x,y).

		@param x
		@param y
		@return tile info
	*/
	TileLegacy getTile(unsigned int x, unsigned int y);

	/*
		Helper function; sets tile at (x,y) to provided tile.

		@param x
		@param y
		@param pointer to new tile
	*/
	void setTile(unsigned int x, unsigned int y, TileLegacy* t);

	/*
		Helper function; sets tiles on rectangle to provided tile.

		@param x
		@param y
		@param width
		@param height
		@param outline tile
	*/
	void setRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height, TileLegacy* outline);

	/*
		Helper function; sets tiles on rectangle to provided tile, and fill to other provided tile.

		@param x
		@param y
		@param width
		@param height
		@param outline tile
		@param fill tile
	*/
	void setRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height, TileLegacy* outline, TileLegacy* fill);

	/*
		Helper function; checks if tile on map is solid.

		@param x
		@param y
		@return solidity of tile at (x,y)
	*/
	bool isSolid(unsigned int x, unsigned int y);

	/*
		Finds entity at (x,y)

		@param x
		@param y
		@returns pointer to entity
	*/
	Entity* getEntity(unsigned int x, unsigned int y);

	/*
		@return width of map
	*/
	unsigned int getWidth();

	/*
		@return height of map
	*/
	unsigned int getHeight();
};

#endif
