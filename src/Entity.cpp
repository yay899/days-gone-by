#include "Entity.hpp"

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
	//Check to see if target is in bounds, and if target is not solid.
	if (map->getWidth() * targetX + targetY < map->getWidth() * map->getHeight() && !map->isSolid(targetX, targetY)) {
		x = targetX;
		y = targetY;
	}

	map->getTilePointer(targetX, targetY)->walkedOn(this);
}

void Entity::moveForce(int targetX, int targetY, Map* map) {
	//Check to see if target is in bounds.
	if (map->getWidth() * targetX + targetY < map->getWidth() * map->getHeight()) {
		x = targetX;
		y = targetY;
	}

	map->getTilePointer(targetX, targetY)->walkedOn(this);
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
		break;
	case TCODK_DOWN:
		move(x, y + 1, map);
		break;
	case TCODK_LEFT:
		move(x - 1, y, map);
		break;
	case TCODK_RIGHT:
		move(x + 1, y, map);
		break;
	default:
		break;
	}
}

void EntityPlayer::render() {
	TCODConsole::root->setCharForeground(x, y, col);
	TCODConsole::root->setChar(x, y, c);
}