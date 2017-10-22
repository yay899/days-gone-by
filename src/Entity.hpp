#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "libtcod.hpp"

//Basic entity. Pretty useless unless extended.
class Entity {
public:
	int x, y; //Position.
	char c; //Character to render as.
	TCODColor col; //Color of character.

	Entity(int x, int y, char c, TCODColor = TCODConsole::root->getDefaultForeground);

	/*
		Takes time since last frame, and pressed key and then does something to the object.

		@parem time
		@parem key
	*/
	virtual void update(float t, TCOD_key_t key);

	/*
		Renders itself.
	*/
	virtual void render();
};

#endif