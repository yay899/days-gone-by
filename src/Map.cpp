#include "Map.hpp"
#include "Engine.hpp"
#include <iostream>

extern Engine _eng;

Map::Map(unsigned int w, unsigned int h) : w(w), h(h) {
	tileMap = new TileLegacy**[h];
    for(int i = 0; i <h; ++i) {
		tileMap[i] = new TileLegacy*[w];
	}


	for (unsigned int  r = 0; r < h; r++) {
		for (unsigned int c = 0; c < w; c++) {
			tileMap[r][c] = new TileLegacy();

		}
	}
}

Map::~Map() {
	for (unsigned int  i= 0; i < h; i++) {
		delete [] tileMap[i];
	}

	delete tileMap;
}

void Map::update() {
	switch (_eng.gameState) {
	case STATE_PLAYER_TURN:
		//Iterate over every player entity in map, calling updater.
		for (std::vector<Entity*>::iterator i = teamPlayer.begin(); i < teamPlayer.end(); i++) {
			(*i)->update(this);
		}
		_eng.gameState = STATE_AI_TURN;
		break;
	case STATE_AI_TURN:
		//Iterate over every AI entity in map, calling updater.
		for (std::vector<Entity*>::iterator i = teamAI.begin(); i < teamAI.end(); i++) {
			(*i)->update(this);
		}
		_eng.gameState = STATE_PLAYER_TURN;
		break;
	default:
		break;
	}

}

void Map::render() {
	for (unsigned int x = 0; x < w; x++) {

		for (unsigned int y = 0; y < h; y++) {
			TileLegacy t = getTile(x, y);
			TCODConsole::root->setChar(x, y, t.c);
			TCODConsole::root->setCharBackground(x, y, t.background);
			TCODConsole::root->setCharForeground(x, y, t.foreground);
		}

	}

	for (std::vector<Entity*>::iterator i = entities.begin(); i < entities.end(); i++) {
		(*i)->render();
	}
}

void Map::addTeamPlayer(Entity* e) {
	teamPlayer.emplace_back(e);
	entities.emplace_back(e);
}

void Map::addTeamAI(Entity* e) {
	teamAI.emplace_back(e);
	entities.emplace_back(e);
}

void Map::generateFill(TileLegacy* t) {
	for (unsigned int  r= 0; r < h; r++) {
		for (unsigned int  c= 0; c < w; c++) {
			delete tileMap[r][c];
			tileMap[r][c] = t;
		}
	}
}

TileLegacy* Map::getTilePointer(unsigned int x, unsigned int y) {
    std::cout<<x<<y<<std::endl;
    std::cout.flush();
	return tileMap[y][x];
}

TileLegacy Map::getTile(unsigned int x, unsigned int y) {
	return *tileMap[y][x];
}

void Map::setTile(unsigned int x, unsigned int y, TileLegacy* t) {
	delete tileMap[y][x];
	tileMap[y][x] = t;
}

void Map::setRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height, TileLegacy* outline) {

	//Draw horizontal portion of outline.
	for (unsigned int i = 0; i < width; i++) {
		setTile(i + x, y, new TileLegacy(outline->c, outline->foreground, outline->background, outline->isSolid));
		setTile(i + x, y + height - 1, new TileLegacy(outline->c, outline->foreground, outline->background, outline->isSolid));
	}

	//Draw vertical portion of outline.
	for (unsigned int i = 1; i < height - 1; i++) { //Start and end one early because the horizontal already covered the corners.
		setTile(x, y + i, new TileLegacy(outline->c, outline->foreground, outline->background, outline->isSolid));
		setTile(x + width - 1, y + i, new TileLegacy(outline->c, outline->foreground, outline->background, outline->isSolid));
	}
}

void Map::setRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height, TileLegacy* outline, TileLegacy* fill) {

	//No need to draw outline individually if the tiles are identical.
	if (outline == fill) {

		//Set all tiles in entire rectangle.
		for (unsigned int i = 0; i < width; i++) {
			for (unsigned int k = 0; k < height; k++) {
				setTile(x + i, y + k, new TileLegacy(outline->c, outline->foreground, outline->background, outline->isSolid));
			}
		}
	} else {

		//Set outline.
		setRectangle(x, y, width, height, outline);

		//Set inside.
		for (unsigned int i = 1; i < width - 1; i++) {
			for (unsigned int k = 1; k < height - 1; k++) {
				setTile(x + i, y + k, new TileLegacy(fill->c, fill->foreground, fill->background, fill->isSolid));
			}
		}
	}
}

bool Map::isSolid(unsigned int x, unsigned int y) {
	//Return solid if there is an entity there.
	for (std::vector<Entity*>::iterator i = entities.begin(); i < entities.end(); i++) {
		if ((*i)->x == x && (*i)->y == y) {
			return true;
		}
	}

	//Otherwise just return the solidity of the tile.

	return tileMap[y][x]->isSolid;
}

Entity* Map::getEntity(unsigned int x, unsigned int y) {
	for (std::vector<Entity*>::iterator i = entities.begin(); i < entities.end(); i++) {
		if ((*i)->x == x && (*i)->y == y) {
			return *i;
		}
	}

	return nullptr;
}

unsigned int Map::getWidth() { return w; }

unsigned int Map::getHeight() { return h; }
