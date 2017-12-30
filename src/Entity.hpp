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

	/**
		@param x
		@param y
		@param character to represent entity
		@param is player?
		@param color of entity
	*/
	Entity(int, int, char, bool, TCODColor = TCODConsole::root->getDefaultForeground());
	~Entity();

	/**
		Pressed key and then does something to the object.

		@param floor entity is on
	*/
	bool update(Floor*);

	/**
		Renders itself.
	*/
	void render();

	/**
		Attacks entity at target

		@param x coordinate
		@param y coordinate
		@param floor entity is on
	*/
	void attack(unsigned int, unsigned int, Floor*);

	/**
		Checks to see if target is solid and then moves object there if it isn't. Runs walkedOn() regardless of whether or not the entity is actually moved.

		@param target x
		@param target y
		@param floor entity is on
	*/
	void move(unsigned int, unsigned int, Floor*);

	/**
		Same as move(), but it ignores checks for solidity.

		@param target x
		@param target y
		@param floor entity is on
	*/
	void moveForce(unsigned int, unsigned int, Floor*);

	/**
		Reduces the entities HP. Negative numbers heal.

		@param damage done
		@return true if entity survived
	*/
	bool hurt(int);

	/**
		Reduces the entities Watts. Negative numbers restore Watts.

		@param watts drained
		@return true if entity has enough Watts
	*/
	bool drain(int);

	/**
		Destroys the entity. When inventory is implimented, drops items, etc.
	*/
	void kill();

	/**
		Asks the AI control module whether the player is controlling this entity
	*/
	bool isPlayer();

	/**
		Calls the interact function on a tile

		@param the x coordinate of the tile in question
		@param the y coordinate of the tile in question
		@param floor pointer to the current floor
	*/
	void interact(int,int, Floor*);
};

/*
	Constants
*/

const int DEFAULT_PLAYER_MAXHP = 10;
const int DEFAULT_PLAYER_MAXWATTS = 10;
const int DEFAULT_TESTENEMY_MAXHP = 10;
const int DEFAULT_TESTENEMY_MAXWATTS = 10;
#endif
