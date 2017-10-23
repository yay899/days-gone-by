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

/*
	Class TileDoor
*/
TileDoor::TileDoor(Tile openTile, Tile closedTile) : Tile(closedTile.c, closedTile.foreground, closedTile.background, closedTile.isSolid), openTile(openTile), closedTile(closedTile) {

}

void TileDoor::open() {
	c = openTile.c;
	foreground = openTile.foreground;
	background = openTile.background;
	isSolid = openTile.isSolid;
}

void TileDoor::closed() {
	c = closedTile.c;
	foreground = closedTile.foreground;
	background = closedTile.background;
	isSolid = closedTile.isSolid;
}

void TileDoor::walkedOn(Entity* e, Map* map) {
	open();
}