#include "Entity.hpp"

/*
	Class Entity.
*/
Entity::Entity(int x, int y, char c, TCODColor col) : x(x), y(y), c(c), col(col) {

}

void Entity::update(float t, TCOD_key_t) {
	//Define this when extending.
}

void Entity::render() {
	//Define this when extending.
}