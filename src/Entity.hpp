#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "libtcod.hpp"
#include "Map.hpp"

//Need to declare this here due to cyclical #includes.
class Map;

//Basic entity. Pretty useless unless extended.
class Entity {
public:
	int x, y; //Position.
	char c; //Character to render as.
	TCODColor col; //Color of character.

	int hp, maxHp;
	int watts, maxWatts;

	Entity(int x, int y, char c, TCODColor = TCODConsole::root->getDefaultForeground());

	/*
		Takes time since last frame, and pressed key and then does something to the object.

		@param time
		@param keycode
		@param map entity is on
	*/
	virtual void update(float t, TCOD_key_t key, Map* map);

	/*
		Renders itself.
	*/
	virtual void render();

	/*
		Checks to see if target is solid and then moves object there if it isn't. Runs walkedOn() regardless of whether or not the entity is actually moved.

		@param target x
		@param target y
		@param map entity is on
	*/
	void move(unsigned int targetX, unsigned int targetY, Map* map);

	/*
		Same as move(), but it ignores checks for solidity.

		@param target x
		@param target y
		@param map entity is on
	*/
	void moveForce(unsigned int targetX, unsigned int targetY, Map* map);

	/*
		Reduces the entities HP. Negative numbers heal.

		@param damage done
		@returns true if entity survived
	*/
	bool hurt(int x);

	/*
		Reduces the entities Watts. Negative numbers restore Watts.

		@param watts drained
		@returns true if entity has enough Watts
	*/
	bool drain(int x);

	/*
		Destroys the entity. When inventory is implimented, drops items, etc.
	*/
	void kill();
};

class EntityPlayer : public Entity {
public:

	EntityPlayer(int x, int y, char c, TCODColor = TCODConsole::root->getDefaultForeground());

	/*
		Extends Entity::update() with player functionality.

		@param time
		@param keycode
		@param map entity is on
	*/
	void update(float t, TCOD_key_t key, Map* map);

	/*
		Extends Entity::render() with player functionality.
	*/
	void render();
};

/*
	Test enemy. Please ignore. (67k upvotes)
*/
class EntityTestEnemy : public Entity {
public:

	EntityTestEnemy(int x, int y, char c, TCODColor = TCODConsole::root->getDefaultForeground());

	/*
		Extends Entity::update() with test enemy functionality.

		@param time
		@param keycode
		@param map entity is on
	*/
	void update(float t, TCOD_key_t key, Map* map);

	/*
		Extends Entity::render() with test enemy functionality.
	*/
	void render();
};
#endif