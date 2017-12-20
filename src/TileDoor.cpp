#include "TileDoor.hpp"

TileDoor::TileDoor(char opCh, char clCh, bool cl, bool oc, bool wa, bool op) : clear(cl), closedCharacter(clCh), occupied(oc), open(op), openCharacter(opCh), walkable(wa) {

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
	TCODConsole::root->setChar(c, r, open ? openCharacter : closedCharacter);
}