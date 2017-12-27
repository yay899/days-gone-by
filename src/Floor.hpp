#pragma once
#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "libtcod.hpp"

#include "TileNormal.hpp"
#include "TileDoor.hpp"

#include "Entity.hpp"

//Need to declare this here due to cyclical #includes.
class Entity;

class Floor {
protected:
    friend class BspListener;
	unsigned int w, h;
	Tile*** tileMap; //Floor of tiles.


public:
	void generateMap();
	std::vector<Entity*> entities; //All entities in floor.
	std::vector<Entity*> teamPlayer; //ONLY player entities.
	std::vector<Entity*> teamAI; //Everything else.

	/**
		@param width
		@param height
	*/
	Floor(unsigned int, unsigned int);
	~Floor();

	/**
		Updates all entities in floor.
	*/
	void update();

	/**
		Displays the contents of the floor on TCODConsole->root.
	*/
	void render();

	/**
		Helper function; add entity to teamPlayer and entities.

		@param pointer to new entity
	*/
	void addTeamPlayer(Entity*);

	/**
		Helper function; add entity to teamAI and entities.

		@param pointer to new entity
	*/
	void addTeamAI(Entity*);

	/**
		Fills floor with a single tile.

		@template type of tile
		@param desired tile
	*/
	template <class TileType>
	void generateFill(TileType);

	//TODO write more generators.

	/**
		Helper function; gets tile info at (c,r).

		@param c
		@param r
		@return tile info
	*/
	Tile& getTile(unsigned int, unsigned int);

	/**
		Helper function; sets tile at (r,c) to provided tile.

		@template tile type
		@param r
		@param c
		@param new tile
	*/
	template <class TileType>
	void setTile(unsigned int, unsigned int, TileType);

	/**
		Helper function; sets tiles on rectangle to provided tile.

		@template tile type
		@param r
		@param c
		@param width
		@param height
		@param outline tile
	*/
	template <class TileType>
	void setRectangle(unsigned int, unsigned int, unsigned int, unsigned int, TileType);

	/**
		Helper function; sets tiles on rectangle to provided tile, and fill to other provided tile.

		@template tile type
		@param r
		@param c
		@param width
		@param height
		@param outline tile
		@param fill tile
	*/
	template <class TileType>
	void setRectangle(unsigned int, unsigned int, unsigned int, unsigned int, TileType, TileType);

	/**
		Helper function; checks if tile on floor is solid.

		@param r
		@param c
		@return solidity of tile at (r,c)
	*/
	bool isSolid(unsigned int, unsigned int);

	/**
		Finds entity at (r,c)

		@param r
		@param c
		@return pointer to entity
	*/
	Entity* getEntity(unsigned int, unsigned int);

  /**
    Returns a reference to the player controlled unit which will take a turn next

    @return a referece to a player controlled entity. nullptr if none.
  */
  Entity* getPlayer();

  /**
		@return width of floor
	*/
	unsigned int getWidth();

	/**
		@return height of floor
	*/
	unsigned int getHeight();
};

#endif
