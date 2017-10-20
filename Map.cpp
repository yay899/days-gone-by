#include "Map.hpp"

Map::Map(int w, int h) : w(w), h(h) {
	tileMap = new Tile*[w*h];

	for (int i = 0; i < w*h; i++) {
		tileMap[i] = new Tile();
	}
}

Map::~Map() {
	for (int i = 0; i < w*h; i++) {
		delete tileMap[i];
	}
	
	delete tileMap;
}

void Map::render() {
	//TODO impliment this.
}

void Map::generateFill(Tile t) {
	for (int i = 0; i < w*h; i++) {
		*(tileMap[i]) = t;
	}
}

Tile* Map::getTilePointer(int x, int y) {
	return tileMap[w * x + y];
}

Tile Map::getTile(int x, int y) {
	return *(tileMap[w * x + y]);
}

void Map::setTile(int x, int y, Tile t) {
	*(tileMap[w * x + y]) = t;
}

bool Map::isSolid(int x, int y) {
	return tileMap[w * x + y]->isSolid;
}