#include "Map.hpp"
#include "Engine.hpp"

extern Engine _eng;

Map::Map(unsigned int w, unsigned int h) : w(w), h(h) {
	tileMap = new Tile*[w*h];

	for (unsigned int i = 0; i < w*h; i++) {
		tileMap[i] = new Tile();
	}
}

Map::~Map() {
	for (unsigned int i = 0; i < w*h; i++) {
		delete tileMap[i];
	}
	
	delete tileMap;
}

void Map::update(float t, TCOD_key_t key) {
	switch (_eng.gameState) {
	case STATE_PLAYER_TURN:
		//Iterate over every player entity in map, calling updater.
		for (std::vector<Entity*>::iterator i = teamPlayer.begin(); i < teamPlayer.end(); i++) {
			(*i)->update(t, key, this);
		}
		break;
	case STATE_AI_TURN:
		//Iterate over every AI entity in map, calling updater.
		for (std::vector<Entity*>::iterator i = teamAI.begin(); i < teamAI.end(); i++) {
			(*i)->update(t, key, this);
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
			Tile t = getTile(x, y);
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

void Map::generateFill(Tile t) {
	for (unsigned int i = 0; i < w*h; i++) {
		*tileMap[i] = t;
	}
}

Tile* Map::getTilePointer(unsigned int x, unsigned int y) {
	return tileMap[h * x + y];
}

Tile Map::getTile(unsigned int x, unsigned int y) {
	return *tileMap[h * x + y];
}

void Map::setTile(unsigned int x, unsigned int y, Tile* t) {
	delete tileMap[h * x + y];
	tileMap[h * x + y] = t;
}

void Map::setRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height, Tile outline) {
	
	//Draw horizontal portion of outline.
	for (unsigned int i = 0; i < width; i++) {
		setTile(i + x, y, new Tile(outline));
		setTile(i + x, y + height - 1, new Tile(outline));
	}

	//Draw vertical portion of outline.
	for (unsigned int i = 1; i < height - 1; i++) { //Start and end one early because the horizontal already covered the corners.
		setTile(x, y + i, new Tile(outline));
		setTile(x + width - 1, y + i, new Tile(outline));
	}
}

void Map::setRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height, Tile outline, Tile fill) {

	//No need to draw outline individually if the tiles are identical.
	if (outline == fill) {

		//Set all tiles in entire rectangle.
		for (unsigned int i = 0; i < width; i++) {
			for (unsigned int k = 0; k < height; k++) {
				setTile(x + i, y + k, new Tile(outline));
			}
		}
	} else {
		
		//Set outline.
		setRectangle(x, y, width, height, outline);

		//Set inside.
		for (unsigned int i = 1; i < width - 1; i++) {
			for (unsigned int k = 1; k < height - 1; k++) {
				setTile(x + i, y + k, new Tile(fill));
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
	return tileMap[h * x + y]->isSolid;
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