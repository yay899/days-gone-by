#include "Entity.hpp"
#include "update.hpp"

//Declare this so it'll actually recognize that it exists.
extern State _gameState;

/*
	Class Entity.
*/
Entity::Entity(int x, int y, char c, TCODColor col) : x(x), y(y), c(c), col(col) {

}

void Entity::update(float t, TCOD_key_t key, Map* map) {
	//Define this when extending.
}

void Entity::render() {
	//Define this when extending.
}

void Entity::move(int targetX, int targetY, Map* map) {
	//Check to see if target is in bounds.
	if (targetX >= 0 && targetY >= 0 && map->getWidth() * targetX + targetY < map->getWidth() * map->getHeight()) {
		//Check to see if target is solid.
		if (!map->isSolid(targetX, targetY)) {
			x = targetX;
			y = targetY;
		}

		map->getTilePointer(targetX, targetY)->walkedOn(this, map);
	}
}

void Entity::moveForce(int targetX, int targetY, Map* map) {
	//Check to see if target is in bounds.
	if (targetX >= 0 && targetY >= 0 && map->getWidth() * targetX + targetY < map->getWidth() * map->getHeight()) {
		x = targetX;
		y = targetY;

		map->getTilePointer(targetX, targetY)->walkedOn(this, map);
	}
}

/*
	Class EntityPlayer.
*/
EntityPlayer::EntityPlayer(int x, int y, char c, TCODColor col) : Entity(x, y, c, col) {

}

void EntityPlayer::update(float t, TCOD_key_t key, Map* map) {

	switch (key.vk) {
	//Characters.
	case TCODK_CHAR:
		switch (key.c) {
		case '.':
			_gameState = STATE_AI_TURN;
		default:
			break;
		}
		break;
	//Special keys.
	case TCODK_UP:
		move(x, y - 1, map);
		_gameState = STATE_AI_TURN;
		break;
	case TCODK_DOWN:
		move(x, y + 1, map);
		_gameState = STATE_AI_TURN;
		break;
	case TCODK_LEFT:
		move(x - 1, y, map);
		_gameState = STATE_AI_TURN;
		break;
	case TCODK_RIGHT:
		move(x + 1, y, map);
		_gameState = STATE_AI_TURN;
		break;
	case TCODK_KP1:
		move(x - 1, y + 1, map);
		_gameState = STATE_AI_TURN;
		break;
	case TCODK_KP2:
		move(x, y + 1, map);
		_gameState = STATE_AI_TURN;
		break;
	case TCODK_KP3:
		move(x + 1, y + 1, map);
		_gameState = STATE_AI_TURN;
		break;
	case TCODK_KP4:
		move(x - 1, y, map);
		_gameState = STATE_AI_TURN;
		break;
	case TCODK_KP5:
		_gameState = STATE_AI_TURN;
		break;
	case TCODK_KP6:
		move(x + 1, y, map);
		_gameState = STATE_AI_TURN;
		break;
	case TCODK_KP7:
		move(x - 1, y - 1, map);
		_gameState = STATE_AI_TURN;
		break;
	case TCODK_KP8:
		move(x, y - 1, map);
		_gameState = STATE_AI_TURN;
		break;
	case TCODK_KP9:
		move(x + 1, y - 1, map);
		_gameState = STATE_AI_TURN;
		break;
	default:
		break;
	}
}

void EntityPlayer::render() {
	TCODConsole::root->setCharForeground(x, y, col);
	TCODConsole::root->setChar(x, y, c);
}

/*
	Class EntityTestEnemy
*/

EntityTestEnemy::EntityTestEnemy(int x, int y, char c, TCODColor col) : Entity(x, y, c, col) {

}

void EntityTestEnemy::update(float t, TCOD_key_t key, Map* map) {
	int targetX(x), targetY(y);

	//Target one tile in the direction of the player.
	if (map->teamPlayer.at(0)->x > x) {
		targetX++;
	}
	else if (map->teamPlayer.at(0)->x < x) {
		targetX--;
	}

	if (map->teamPlayer.at(0)->y > y) {
		targetY++;
	}
	else if (map->teamPlayer.at(0)->y < y) {
		targetY--;
	}

	//Move if the target is actually somewhere other than current position.
	if (targetX != x || targetY != y) {
		move(targetX, targetY, map);
	}
}

void EntityTestEnemy::render() {
	TCODConsole::root->setCharForeground(x, y, col);
	TCODConsole::root->setChar(x, y, c);
}