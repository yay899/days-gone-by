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

void Map::update(float t, TCOD_key_t key) {
	//Iterate over every entity in map, calling updater.
	for (std::vector<Entity*>::iterator i = entities.begin(); i < entities.end(); i++) {
		(*i)->update(t, key, this);
	}
}

void Map::render() {
	for (int x = 0; x < w; x++) {

		for (int y = 0; y < h; y++) {
			Tile t = getTile(x, y);
			TCODConsole::root->setChar(x, y, t.c);
			TCODConsole::root->setCharBackground(x, y, t.background);
			TCODConsole::root->setCharForeground(x, y, t.foreground);
		}

	}
}

void Map::generateFill(Tile t) {
	for (int i = 0; i < w*h; i++) {
		*tileMap[i] = t;
	}
}

Tile* Map::getTilePointer(int x, int y) {
	return tileMap[w * x + y];
}

Tile Map::getTile(int x, int y) {
	return *tileMap[w * x + y];
}

void Map::setTile(int x, int y, Tile t) {
	*tileMap[w * x + y] = t;
}

void Map::setRectangle(int x, int y, int width, int height, Tile outline) {
	
	//Draw horizontal portion of outline.
	for (int i = 0; i < width; i++) {
		setTile(i + x, y, outline);
		setTile(i + x, y + height - 1, outline);
	}

	//Draw vertical portion of outline.
	for (int i = 1; i < height - 1; i++) { //Start and end one early because the horizontal already covered the corners.
		setTile(x, y + i, outline);
		setTile(x + width - 1, y + i, outline);
	}
}

void Map::setRectangle(int x, int y, int width, int height, Tile outline, Tile fill) {

	//No need to draw outline individually if the tiles are identical.
	if (outline == fill) {

		//Set all tiles in entire rectangle.
		for (int i = 0; i < width; i++) {
			for (int k = 0; k < height; k++) {
				setTile(x + i, y + k, outline);
			}
		}
	} else {
		
		//Set outline.
		setRectangle(x, y, width, height, outline);

		//Set inside.
		for (int i = 1; i < width - 1; i++) {
			for (int k = 1; k < height - 1; k++) {
				setTile(x + i, y + k, fill);
			}
		}
	}
}

bool Map::isSolid(int x, int y) {
	return tileMap[w * x + y]->isSolid;
}

int Map::getWidth() { return w; }

int Map::getHeight() { return h; }