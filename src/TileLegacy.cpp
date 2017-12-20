#include "TileLegacy.hpp"

/*
	Class Tile.
*/
TileLegacy::TileLegacy(char c, TCODColor foreground, TCODColor background, bool isSolid) : c(c), foreground(foreground), background(background), isSolid(isSolid) {

}

const bool TileLegacy::operator==(const TileLegacy &other) {
	return (this->c == other.c
		&& this->foreground == other.foreground
		&& this->background == other.background
		&& this->isSolid == other.isSolid);
}

const bool TileLegacy::operator!=(const TileLegacy &other) {
	return !(*this == other);
}

void TileLegacy::walkedOn(Entity* e, Map* map) {

	//Put stuff here when extending this class.

}

/*
	Class TileTeleport
*/

TileTeleport::TileTeleport(char c, TCODColor foreground, TCODColor background, bool isSolid, int x, int y) : TileLegacy(c, foreground, background, isSolid), x(x), y(y) {

}

void TileTeleport::walkedOn(Entity* e, Map* map) {
	e->moveForce(x, y, map);
}

/*
	Class TileDoor
*/
TileDoor::TileDoor(TileLegacy openTile, TileLegacy closedTile) : TileLegacy(closedTile.c, closedTile.foreground, closedTile.background, closedTile.isSolid), openTile(openTile), closedTile(closedTile) {

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