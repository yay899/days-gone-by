#include "Entity.hpp"
#include "Engine.hpp"
#include <iostream>

extern Engine _eng;

/*
	Class Entity.
*/
Entity::Entity(int x, int y, char c, TCODColor col) : x(x), y(y), c(c), col(col), hp(0), maxHp(0), watts(0), maxWatts(0) {

}

void Entity::update(float t, TCOD_key_t key, Floor* floor) {
	//Define this when extending.
}

void Entity::render() {
	//Define this when extending.
}

void Entity::attack(unsigned int targetX, unsigned int targetY, Floor* floor) {
	//Define this when extending.
}

void Entity::move(unsigned int targetX, unsigned int targetY, Floor* floor) {
	//Check to see if target is in bounds.
	if (targetX >= 0 && targetY >= 0 && targetX < floor->getWidth() && targetY < floor->getHeight()) {
		//Check to see if target is solid.
		if (!floor->isSolid(targetX, targetY)) {
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
	if (targetX >= 0 && targetY >= 0 && targetX < floor->getWidth() && targetY < floor->getHeight()) {
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

/*
	Class EntityPlayer.
*/
EntityPlayer::EntityPlayer(int x, int y, char c, TCODColor col) : Entity(x, y, c, col) {

}

void EntityPlayer::update(float t, TCOD_key_t key, Floor* floor) {

	switch (key.vk) {
	//Characters.
	case TCODK_CHAR:
		switch (key.c) {
		case '.':
			_eng.gameState = STATE_AI_TURN;
		default:
			break;
		}
		break;
	//Special keys.
	case TCODK_UP:
		move(x, y - 1, floor);
		_eng.gameState = STATE_AI_TURN;
		break;
	case TCODK_DOWN:
		move(x, y + 1, floor);
		_eng.gameState = STATE_AI_TURN;
		break;
	case TCODK_LEFT:
		move(x - 1, y, floor);
		_eng.gameState = STATE_AI_TURN;
		break;
	case TCODK_RIGHT:
		move(x + 1, y, floor);
		_eng.gameState = STATE_AI_TURN;
		break;
	case TCODK_KP1:
		move(x - 1, y + 1, floor);
		_eng.gameState = STATE_AI_TURN;
		break;
	case TCODK_KP2:
		move(x, y + 1, floor);
		_eng.gameState = STATE_AI_TURN;
		break;
	case TCODK_KP3:
		move(x + 1, y + 1, floor);
		_eng.gameState = STATE_AI_TURN;
		break;
	case TCODK_KP4:
		move(x - 1, y, floor);
		_eng.gameState = STATE_AI_TURN;
		break;
	case TCODK_KP5:
		_eng.gameState = STATE_AI_TURN;
		break;
	case TCODK_KP6:
		move(x + 1, y, floor);
		_eng.gameState = STATE_AI_TURN;
		break;
	case TCODK_KP7:
		move(x - 1, y - 1, floor);
		_eng.gameState = STATE_AI_TURN;
		break;
	case TCODK_KP8:
		move(x, y - 1, floor);
		_eng.gameState = STATE_AI_TURN;
		break;
	case TCODK_KP9:
		move(x + 1, y - 1, floor);
		_eng.gameState = STATE_AI_TURN;
		break;
	default:
		break;
	}
}

void EntityPlayer::render() {
	TCODConsole::root->setCharForeground(x, y, col);
	TCODConsole::root->setChar(x, y, c);
}

void EntityPlayer::attack(unsigned int x, unsigned int y, Floor* floor) {
	Entity* target = floor->getEntity(x, y);
	if (target != nullptr) target->hurt(4);
}

/*
	Class EntityTestEnemy
*/

EntityTestEnemy::EntityTestEnemy(int x, int y, char c, TCODColor col) : Entity(x, y, c, col) {

}

void EntityTestEnemy::update(float t, TCOD_key_t key, Floor* floor) {
	int targetX(x), targetY(y);

	//Target one tile in the direction of the player.
	if (floor->teamPlayer.at(0)->x > x) {
		targetX++;
	}
	else if (floor->teamPlayer.at(0)->x < x) {
		targetX--;
	}

	if (floor->teamPlayer.at(0)->y > y) {
		targetY++;
	}
	else if (floor->teamPlayer.at(0)->y < y) {
		targetY--;
	}

	//Move if the target is actually somewhere other than current position.
	if (targetX != x || targetY != y) {
		move(targetX, targetY, floor);
	}
}

void EntityTestEnemy::render() {
	TCODConsole::root->setCharForeground(x, y, col);
	TCODConsole::root->setChar(x, y, c);
}

void EntityTestEnemy::attack(unsigned int x, unsigned int y, Floor* floor) {
	Entity* target = floor->getEntity(x, y);
	if (target != nullptr) target->hurt(1);
}