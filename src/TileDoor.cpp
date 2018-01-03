#include "TileDoor.hpp"

TileDoor::TileDoor(char opCh, TCODColor opFo, TCODColor opBa, char clCh, TCODColor clFo, TCODColor clBa, bool cl, bool oc, bool wa, bool op) : clear(cl), closedBackgroundColor(clBa), closedCharacter(clCh), closedForegroundColor(clFo), occupied(oc), openBackgroundColor(opBa), open(op), openForegroundColor(opFo), openCharacter(opCh), walkable(wa) {

}

void TileDoor::bumped(Entity& e) {
	open = true;
}

void TileDoor::interact(Entity& e) {
	open = !open;
}

bool TileDoor::isClear() {
	return clear && open;
}

bool TileDoor::isOccupied() {
	return occupied;
}

bool TileDoor::isWalkable() {
	return walkable && !occupied && open;
}

void TileDoor::render(int x, int y) {
	TCODConsole::root->setChar(x, y, open ? openCharacter : closedCharacter);
	TCODConsole::root->setCharForeground(x, y, open ? openForegroundColor : closedForegroundColor);
	TCODConsole::root->setCharBackground(x, y, open ? openBackgroundColor : closedBackgroundColor);
}

void TileDoor::walkedOn(Entity& e) {
	//e.hp = 0;
}