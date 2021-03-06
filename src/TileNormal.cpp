#include "TileNormal.hpp"

TileNormal::TileNormal() : backgroundColor(TCOD_black), character(' '), clear(true), foregroundColor(TCOD_white), occupied(false), seen(UNSEEN), walkable(true) {

}

TileNormal::TileNormal(char ch, TCODColor fo, TCODColor ba, bool cl, bool oc, bool wa) : backgroundColor(ba), character(ch), clear(cl), foregroundColor(fo), occupied(oc), walkable(wa) {

}

void TileNormal::bumped(Entity& e) {
	/*

	*/
}

void TileNormal::interact(Entity& e) {
	backgroundColor = TCOD_red;
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

void TileNormal::render(int x, int y) {
	TCODConsole::root->setChar(x, y, character);
	TCODConsole::root->setCharForeground(x, y, foregroundColor);
	TCODConsole::root->setCharBackground(x, y, backgroundColor);
}

void TileNormal::setSeen(Seen s) {
	seen = s;
}

void TileNormal::walkedOn(Entity& e) {
	/*
		No. Of course you can't.
	*/
}
