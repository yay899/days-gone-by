#include "TileNormal.hpp"

TileNormal::TileNormal(char ch, TCODColor fo, TCODColor ba, bool cl, bool oc, bool wa) : backgroundColor(ba), character(ch), clear(cl), foregroundColor(fo), occupied(oc), walkable(wa) {

}

void TileNormal::bumped(Entity& e) {
	/*
	
	*/
}

void TileNormal::interact(Entity& e) {
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
	TCODConsole::root->setCharForeground(c, r, foregroundColor);
	TCODConsole::root->setCharBackground(c, r, backgroundColor);
}

void TileNormal::walkedOn(Entity& e) {
	/*
		No. Of course you can't.
	*/
}