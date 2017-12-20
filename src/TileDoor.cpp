#include "TileDoor.hpp"

TileDoor::TileDoor(char ch, bool cl, bool oc, bool op, bool wa) : character(ch), clear(cl), occupied(oc), open(op), walkable(wa) {

}

void TileDoor::interact() {
	open = !open;
}

bool TileDoor::isClear() {
	return clear;
}

bool TileDoor::isOccupied() {
	return occupied;
}

bool TileDoor::isWalkable() {
	return walkable && !occupied && open;
}

void TileDoor::render(int r, int c) {
	TCODConsole::root->setChar(c, r, character);
}