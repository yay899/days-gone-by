#include "Tile.hpp"

/*
	Class Tile.
*/
Tile::Tile(char c, TCODColor foreground, TCODColor background, bool isSolid) : c(c), foreground(foreground), background(background), isSolid(isSolid) {

}

const bool Tile::operator==(const Tile &other) {
	return (this->c == other.c
		&& this->foreground == other.foreground
		&& this->background == other.background
		&& this->isSolid == other.isSolid);
}

const bool Tile::operator!=(const Tile &other) {
	return !(*this == other);
}

void Tile::walkedOn(Entity* e, Map* map) {

	//Put stuff here when extending this class.

}

/*
	Class TileTeleport
*/

TileTeleport::TileTeleport(char c, TCODColor foreground, TCODColor background, bool isSolid, int x, int y) : Tile(c, foreground, background, isSolid), x(x), y(y) {

}

void TileTeleport::walkedOn(Entity* e, Map* map) {
	e->moveForce(x, y, map);
}