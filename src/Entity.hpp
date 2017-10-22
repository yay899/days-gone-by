#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "libtcod.hpp"
#include "Map.hpp"

//Basic entity. Pretty useless unless extended.
class Entity {
public:
	int x, y; //Position.
	char c; //Character to render as.
	TCODColor col; //Color of character.

	Entity(int x, int y, char c, TCODColor = TCODConsole::root->getDefaultForeground());

	/*
		Takes time since last frame, and pressed key and then does something to the object.

		@parem time
		@parem keycode
		@parem map entity is on
	*/
	virtual void update(float t, TCOD_keycode_t key, Map* map);

	/*
		Renders itself.
	*/
	virtual void render();

	/*
		Checks to see if target is solid and then moves object there if it isn't. Runs walkedOn() regardless of whether or not the entity is actually moved.

		@parem target x
		@parem target y
		@parem map entity is on
	*/
	void move(int targetX, int targetY, Map* map);

	/*
		Same as move(), but it ignores checks for solidity.

		@parem target x
		@parem target y
		@parem map entity is on
	*/
	void moveForce(int targetX, int targetY, Map* map);
};

class EntityPlayer : Entity {
public:

	EntityPlayer(int x, int y, char c, TCODColor = TCODConsole::root->getDefaultForeground());

	/*
		Extends Entity::update() with player functionality.

		@parem time
		@parem keycode
		@parem map entity is on
	*/
	void update(float t, TCOD_keycode_t key, Map* map);

	/*
		Extends Entity::render() with player functionality.
	*/
	void render();
};

#endif