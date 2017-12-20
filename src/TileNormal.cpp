#include "TileNormal.hpp"

TileNormal::TileNormal(char ch, bool cl, bool oc, bool wa) : character(ch), clear(cl), occupied(oc), walkable(wa) {

}

void TileNormal::interact() {
	/*
		Can you hear it?
	*/
}

bool TileNormal::isClear() {
	return clear;
}

bool TileNormal::isOccupied() {
	return occupied;
}

bool TileNormal::isWalkable() {
	return walkable && !occupied;
}

void TileNormal::render(int r, int c) {
	TCODConsole::root->setChar(c, r, character);
}