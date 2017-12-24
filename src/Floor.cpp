#include "Floor.hpp"

#include "Engine.hpp"
#include <iostream>

extern Engine _eng;

Floor::Floor(unsigned int w, unsigned int h) : w(w), h(h) {
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

Floor::~Floor() {
	for (unsigned int  i= 0; i < h; i++) {
		delete[] tileMap[i];
	}
	
	delete[] tileMap;
}

void Floor::update(float t, TCOD_key_t key) {
	switch (_eng.gameState) {
	case STATE_PLAYER_TURN:
		//Iterate over every player entity in floor, calling updater.
		for (std::vector<Entity*>::iterator i = teamPlayer.begin(); i < teamPlayer.end(); i++) {
			(*i)->update(t, key, this);
		}
		break;
	case STATE_AI_TURN:
		//Iterate over every AI entity in floor, calling updater.
		for (std::vector<Entity*>::iterator i = teamAI.begin(); i < teamAI.end(); i++) {
			(*i)->update(t, key, this);
		}
		_eng.gameState = STATE_PLAYER_TURN;
		break;
	default:
		break;
	}
	
}

void Floor::render() {
	for (unsigned int r = 0; r < h; r++) {
		for (unsigned int c = 0; c < h; c++) {
			getTile(r, c).render(r, c);
		}
	}

	for (std::vector<Entity*>::iterator i = entities.begin(); i < entities.end(); i++) {
		(*i)->render();
	}
}

void Floor::addTeamPlayer(Entity* e) {
	teamPlayer.emplace_back(e);
	entities.emplace_back(e);
}

void Floor::addTeamAI(Entity* e) {
	teamAI.emplace_back(e);
	entities.emplace_back(e);
}

template <class TileType>
void Floor::generateFill(TileType t) {
	for (unsigned int  r = 0; r < h; r++) {
		for (unsigned int c = 0; c < w; c++) {
			delete tileMap[r][c];
			tileMap[r][c] = new TileType(t);
		}
	}
}

Tile& Floor::getTile(unsigned int r, unsigned int c) {
	return *tileMap[r][c];
}

template <class TileType>
void Floor::setTile(unsigned int x, unsigned int y, TileType t) {
	delete tileMap[y][x];
	tileMap[y][x] = new TileType(t);
}

template <class TileType>
void Floor::setRectangle(unsigned int r, unsigned int c, unsigned int width, unsigned int height, TileType outline) {

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
void Floor::setRectangle(unsigned int r, unsigned int c, unsigned int width, unsigned int height, TileType outline, TileType fill) {
	//Set outline.
	setRectangle(r, c, width, height, outline);

	//Set inside.
	for (unsigned int i = 1; i < width - 1; i++) {
		for (unsigned int k = 1; k < height - 1; k++) {
			setTile(r + k, c + i, TileType(fill));
		}
	}
}

bool Floor::isSolid(unsigned int r, unsigned int c) {
	return !getTile(r, c).isWalkable();
}

Entity* Floor::getEntity(unsigned int x, unsigned int y) {
	for (std::vector<Entity*>::iterator i = entities.begin(); i < entities.end(); i++) {
		if ((*i)->x == x && (*i)->y == y) {
			return *i;
		}
	}

	return nullptr;
}

unsigned int Floor::getWidth() { return w; }

unsigned int Floor::getHeight() { return h; }

//Explicit instantiations
template void Floor::generateFill<TileNormal>(TileNormal);
template void Floor::generateFill<TileDoor>(TileDoor);

template void Floor::setRectangle<TileNormal>(unsigned int, unsigned int, unsigned int, unsigned int, TileNormal, TileNormal);
template void Floor::setRectangle<TileDoor>(unsigned int, unsigned int, unsigned int, unsigned int, TileDoor, TileDoor);

template void Floor::setRectangle<TileNormal>(unsigned int, unsigned int, unsigned int, unsigned int, TileNormal);
template void Floor::setRectangle<TileDoor>(unsigned int, unsigned int, unsigned int, unsigned int, TileDoor);

template void Floor::setTile<TileNormal>(unsigned int, unsigned int, TileNormal);
template void Floor::setTile<TileDoor>(unsigned int, unsigned int, TileDoor);