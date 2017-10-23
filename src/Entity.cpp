#include "Entity.hpp"
#include "update.hpp"

//Declare this so it'll actually recognize that it exists.
extern State _gameState;

/*
	Class Entity.
*/
Entity::Entity(int x, int y, char c, TCODColor col) : x(x), y(y), c(c), col(col) {

}

void Entity::update(float t, TCOD_keycode_t key, Map* map) {
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

void EntityPlayer::update(float t, TCOD_keycode_t key, Map* map) {

	switch (key) {
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
	default:
		break;
	}
}

void EntityPlayer::render() {
	TCODConsole::root->setCharForeground(x, y, col);
	TCODConsole::root->setChar(x, y, c);
}