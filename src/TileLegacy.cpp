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

void TileLegacy::walkedOn(Entity* e, Floor* floor) {

	//Put stuff here when extending this class.

}

/*
	Class TileTeleport
*/

TileTeleportLegacy::TileTeleportLegacy(char c, TCODColor foreground, TCODColor background, bool isSolid, int x, int y) : TileLegacy(c, foreground, background, isSolid), x(x), y(y) {

}

void TileTeleportLegacy::walkedOn(Entity* e, Floor* floor) {
	//this throws errors as there is no x and y given
	e->moveForce(x, y, floor);
}

/*
	Class TileDoor
*/
TileDoorLegacy::TileDoorLegacy(TileLegacy openTile, TileLegacy closedTile) : TileLegacy(closedTile.c, closedTile.foreground, closedTile.background, closedTile.isSolid), openTile(openTile), closedTile(closedTile) {

}

void TileDoorLegacy::open() {
	c = openTile.c;
	foreground = openTile.foreground;
	background = openTile.background;
	isSolid = openTile.isSolid;
}

void TileDoorLegacy::closed() {
	c = closedTile.c;
	foreground = closedTile.foreground;
	background = closedTile.background;
	isSolid = closedTile.isSolid;
}

void TileDoorLegacy::walkedOn(Entity* e, Floor* floor) {
	open();
}