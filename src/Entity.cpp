#include "Entity.hpp"
#include "Engine.hpp"
#include "EntityAI.hpp"
#include "EnemyAI.hpp"
#include "PlayerAI.hpp"
#include <iostream>

extern Engine _eng;

/*
	Class Entity.
*/
Entity::Entity(int x, int y, char c, bool player, TCODColor col) : x(x), y(y), c(c), col(col){
	if(player){
		maxHp = DEFAULT_PLAYER_MAXHP;
		maxWatts = DEFAULT_PLAYER_MAXWATTS;
		ai = new PlayerAI(this);
	}
	else{
		maxHp = DEFAULT_TESTENEMY_MAXHP;
		maxWatts = DEFAULT_TESTENEMY_MAXWATTS;
		ai = new EnemyAI(this);
	}
	hp = maxHp;
	watts = maxWatts;
}
Entity::~Entity(){
	delete ai;
}

bool Entity::update(Floor* floor) {
	return ai->takeTurn(floor);
}

void Entity::render() {
	TCODConsole::root->setCharForeground(x, y, col);
	TCODConsole::root->setChar(x, y, c);
}

void Entity::attack(unsigned int targetX, unsigned int targetY, Floor* floor) {
	Entity* target = floor->getEntity(targetX, targetY);
	if (target != nullptr) target->hurt(4);
}

void Entity::move(unsigned int targetX, unsigned int targetY, Floor* floor) {
	//Check to see if target is in bounds.
	if (targetX < floor->getWidth() && targetY < floor->getHeight()) {
		//Check to see if target is solid.
		if (!floor->isSolid(targetY,targetX)) {
			x = targetX;
			y = targetY;
		} else {
			attack(targetX, targetY, floor);
		}

		//this throws errors as it is somehow calling tile teleportLegacy, which does not have initialized x and y coords
		//look into this

		//floor->getTilePointer(targetX, targetY)->walkedOn(this, floor);

	}
}

void Entity::moveForce(unsigned int targetX, unsigned int targetY, Floor* floor) {
	//Check to see if target is in bounds.
	if (targetX < floor->getWidth() && targetY < floor->getHeight()) {
		x = targetX;
		y = targetY;

		//this throws errors as it is somehow calling tile teleportLegacy, which does not have initialized x and y coords
		//look into this
		floor->getTile(targetX, targetY).walkedOn(*this);
	}
}

bool Entity::hurt(int x) {
	hp -= x;
	if (maxHp > 0 && hp <= 0) {
		kill(); //This could be an issue. Not sure if it'll still return false if we deconstruct the entity in this function.
		return false;
	}

	return true;
}

bool Entity::drain(int x) {
	if (watts >= x) {
		watts -= x;
		return true;
	}

	return false;
}

void Entity::kill() {
	col = TCOD_red; //Test code. Just makes the entity red.
}

bool Entity::isPlayer(){
	return ai->isPlayer();
}

void Entity::interact(int tileX, int tileY, Floor* floor){
	floor->getTile(tileY,tileX).interact(*this);	//Switched X and Y because row/column
}
