#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include "libtcod.hpp"
#include "Entity.hpp"

//Basic tile for use in Map.
class Tile {
public:

	char c; //The character this tile on the map renders as.
	TCODColor foreground; //The color of the character.
	TCODColor background; //The color of the tile.
	bool isSolid; //Whether or not the tile is solid.

	Tile(char c = ' ', TCODColor foreground = TCODConsole::root->getDefaultForeground(), TCODColor background = TCODConsole::root->getDefaultBackground(), bool isSolid = false);

	/*
		Overload == and != so they function. Hopefully this works. Stole most of it off the internet.
	*/
	const bool operator==(const Tile &other);
	const bool operator!=(const Tile &other);

	/*
		Called when tile is walked on, to enable complex tile functionality

		@param entity that entered tile
	*/
	virtual void walkedOn(Entity* e); //TODO Make this take an entity as an argument when those are implimented.
};

/*
	Tile constants.
	Basically presets. That's why they're global.
*/
const Tile TILE_FLOOR = Tile(' ', TCOD_white, TCOD_black, false);
const Tile TILE_WALL = Tile(' ', TCOD_white, TCOD_blue, true);
const Tile TILE_FANCYFLOOR = Tile('+', TCOD_white, TCOD_azure, false);
const Tile TILE_FANCYWALL = Tile('#', TCOD_white, TCOD_blue, true);
#endif