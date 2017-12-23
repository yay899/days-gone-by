#pragma once
#ifndef TILE_LEGACY_HPP
#define TILE_LEGACY_HPP

#include "libtcod.hpp"
#include "Entity.hpp"
#include "Map.hpp"

//Need to declare this here due to cyclical #includes.
class Entity;
class Map;

//Basic tile for use in Map.
class TileLegacy {
public:

	char c; //The character this tile on the map renders as.
	TCODColor foreground; //The color of the character.
	TCODColor background; //The color of the tile.
	bool isSolid; //Whether or not the tile is solid.

	TileLegacy(char c = ' ', TCODColor foreground = TCODConsole::root->getDefaultForeground(), TCODColor background = TCODConsole::root->getDefaultBackground(), bool isSolid = false);

	/*
		Overload == and != so they function. Hopefully this works. Stole most of it off the internet.
	*/
	const bool operator==(const TileLegacy &other);
	const bool operator!=(const TileLegacy &other);

	/*
		Called when tile is walked on, to enable complex tile functionality

		@param entity that entered tile
		@param map tile is on
	*/
	virtual void walkedOn(Entity* e, Map* map); //TODO Make this take an entity as an argument when those are implimented.
};

//Tile that teleports anything that walks on it.
class TileTeleportLegacy : public TileLegacy {
public:

	int x, y; //Target tile to teleport to

	TileTeleportLegacy(char c = ' ', TCODColor foreground = TCODConsole::root->getDefaultForeground(), TCODColor background = TCODConsole::root->getDefaultBackground(), bool isSolid = false, int x = 0, int y = 0);

	/*
		Teleports entity that enters tile to target.

		@param entity that entered tile
		@param map tile is on
	*/
	void walkedOn(Entity* e, Map* map);
};

class TileDoorLegacy : public TileLegacy {
public:
	TileLegacy openTile, closedTile; //Both states of doors.

	//Initializes closed.
	TileDoorLegacy(TileLegacy openTile, TileLegacy closedTile);

	/*
		Opens door.
	*/
	void open();

	/*
		Closes door.
	*/
	void closed();

	/*
		Opens door when entity attempts to enter it.

		@param entity that entered tile
		@param map tile is on
	*/
	void walkedOn(Entity* e, Map* map);
};

/*
	Tile constants.
	Basically presets. That's why they're global.
 	these do not work as they are const and functions need to be const to accept them
*/
const TileLegacy TILE_FLOOR = TileLegacy(' ', TCOD_white, TCOD_black, false);
const TileLegacy TILE_WALL = TileLegacy(' ', TCOD_white, TCOD_blue, true);
const TileLegacy TILE_FANCYFLOOR = TileLegacy('+', TCOD_white, TCOD_azure, false);
const TileLegacy TILE_FANCYWALL = TileLegacy('#', TCOD_white, TCOD_blue, true);

const TileDoorLegacy TILEDOOR_DOOR = TileDoorLegacy(TileLegacy('+', TCOD_amber, TCOD_black, false), TileLegacy('#', TCOD_white, TCOD_amber, true));
#endif