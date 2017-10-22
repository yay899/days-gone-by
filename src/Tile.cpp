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

void Tile::walkedOn() {

	//Put stuff here when extending this class.

}