#include "Map.hpp"

#include "Engine.hpp"
#include <iostream>

extern Engine _eng;

Map::Map(unsigned int w, unsigned int h) : w(w), h(h) {
	tileMap = new Tile**[h];
    for(unsigned int i = 0; i < h; ++i) {
		tileMap[i] = new Tile*[w];
	}


	for (unsigned int  r = 0; r < h; r++) {
		for (unsigned int c = 0; c < w; c++) {
			tileMap[r][c] = new TileNormal();
		}
	}
}

Map::~Map() {
	for (unsigned int  i= 0; i < h; i++) {
		delete[] tileMap[i];
	}
	
	delete[] tileMap;
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
	for (unsigned int r = 0; r < h; r++) {
		for (unsigned int c = 0; c < h; c++) {
			getTile(r, c).render(r, c);
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

template <class TileType>
void Map::generateFill(TileType t) {
	for (unsigned int  r = 0; r < h; r++) {
		for (unsigned int c = 0; c < w; c++) {
			delete tileMap[r][c];
			tileMap[r][c] = new TileType(t);
		}
	}
}

Tile& Map::getTile(unsigned int r, unsigned int c) {
	return *tileMap[r][c];
}

template <class TileType>
void Map::setTile(unsigned int x, unsigned int y, TileType t) {
	delete tileMap[y][x];
	tileMap[y][x] = new TileType(t);
}

template <class TileType>
void Map::setRectangle(unsigned int r, unsigned int c, unsigned int width, unsigned int height, TileType outline) {

	//Draw horizontal portion of outline.
	for (unsigned int i = 0; i < width; i++) {
		setTile(r, c + i, TileType(outline));
		setTile(r + height - 1, c +i, TileType(outline));
	}

	//Draw vertical portion of outline.
	for (unsigned int i = 1; i < height - 1; i++) { //Start and end one early because the horizontal already covered the corners.
		setTile(r + i, c, TileType(outline));
		setTile(r + i, c + width - 1, TileType(outline));
	}
}

template <class TileType>
void Map::setRectangle(unsigned int r, unsigned int c, unsigned int width, unsigned int height, TileType outline, TileType fill) {
	//Set outline.
	setRectangle(r, c, width, height, outline);

	//Set inside.
	for (unsigned int i = 1; i < width - 1; i++) {
		for (unsigned int k = 1; k < height - 1; k++) {
			setTile(r + k, c + i, TileType(fill));
		}
	}
}

bool Map::isSolid(unsigned int r, unsigned int c) {
	return !getTile(r, c).isWalkable();
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

//Explicit instantiations
template void Map::generateFill<TileNormal>(TileNormal);
template void Map::generateFill<TileDoor>(TileDoor);

template void Map::setRectangle<TileNormal>(unsigned int, unsigned int, unsigned int, unsigned int, TileNormal, TileNormal);
template void Map::setRectangle<TileDoor>(unsigned int, unsigned int, unsigned int, unsigned int, TileDoor, TileDoor);

template void Map::setRectangle<TileNormal>(unsigned int, unsigned int, unsigned int, unsigned int, TileNormal);
template void Map::setRectangle<TileDoor>(unsigned int, unsigned int, unsigned int, unsigned int, TileDoor);

template void Map::setTile<TileNormal>(unsigned int, unsigned int, TileNormal);
template void Map::setTile<TileDoor>(unsigned int, unsigned int, TileDoor);