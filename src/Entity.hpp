#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "libtcod.hpp"
#include "Floor.hpp"
#include "EntityAI.hpp"

//Need to declare this here due to cyclical #includes.
class Floor;

//Basic entity. Pretty useless unless extended.
class Entity {
public:
	int x, y; //Position.
	char c; //Character to render as.
	TCODColor col; //Color of character.

	int hp, maxHp;
	int watts, maxWatts;
	EntityAI *ai;

	Entity(int x, int y, char c, bool player, TCODColor = TCODConsole::root->getDefaultForeground());
	~Entity();

	/*
		pressed key and then does something to the object.

		@param keycode
		@param floor entity is on
	*/
    //CHANGE PARAMS IN CORR CLASS
	bool update(Floor* floor);

	/*
		Renders itself.
	*/
	void render();

	/*
		Attacks entity at target

		@param x coordinate
		@param y coordinate
		@param floor entity is on
	*/
	void attack(unsigned int targetX, unsigned int targetY, Floor* floor);

	/*
		Checks to see if target is solid and then moves object there if it isn't. Runs walkedOn() regardless of whether or not the entity is actually moved.

		@param target x
		@param target y
		@param floor entity is on
	*/
	void move(unsigned int targetX, unsigned int targetY, Floor* floor);

	/*
		Same as move(), but it ignores checks for solidity.

		@param target x
		@param target y
		@param floor entity is on
	*/
	void moveForce(unsigned int targetX, unsigned int targetY, Floor* floor);

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

/*
	Constants
*/

const int DEFAULT_PLAYER_MAXHP = 10;
const int DEFAULT_PLAYER_MAXWATTS = 10;
const int DEFAULT_TESTENEMY_MAXHP = 10;
const int DEFAULT_TESTENEMY_MAXWATTS = 10;
#endif