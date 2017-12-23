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

void Entity::update(TCOD_key_t key, Map* map) {
	ai->takeTurn(map);
}

void Entity::render() {
	TCODConsole::root->setCharForeground(x, y, col);
	TCODConsole::root->setChar(x, y, c);
}

void Entity::attack(unsigned int targetX, unsigned int targetY, Map* map) {
	Entity* target = map->getEntity(targetX, targetY);
	if (target != nullptr) target->hurt(4);
}

void Entity::move(unsigned int targetX, unsigned int targetY, Map* map) {
	//Check to see if target is in bounds.
	if (targetX >= 0 && targetY >= 0 && targetX < map->getWidth() && targetY < map->getHeight()) {
		//Check to see if target is solid.
		if (!map->isSolid(targetX, targetY)) {
			x = targetX;
			y = targetY;
		} else {
			attack(targetX, targetY, map);
		}

		//this throws errors as it is somehow calling tile teleportLegacy, which does not have initialized x and y coords
		//look into this

		//map->getTilePointer(targetX, targetY)->walkedOn(this, map);

	}
}

void Entity::moveForce(unsigned int targetX, unsigned int targetY, Map* map) {
	//Check to see if target is in bounds.
	if (targetX >= 0 && targetY >= 0 && targetX < map->getWidth() && targetY < map->getHeight()) {
		x = targetX;
		y = targetY;

		//this throws errors as it is somehow calling tile teleportLegacy, which does not have initialized x and y coords
		//look into this
		map->getTilePointer(targetX, targetY)->walkedOn(this, map);
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
