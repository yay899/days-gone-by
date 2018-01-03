#include "Floor.hpp"

#include "Engine.hpp"
#include "FloorGenListener.hpp"
#include <iostream>

template <class TileType>
void Floor::generateMap(TileType outline, TileType fill){
	TCODBsp bsp(0,0,w,h);
	bsp.splitRecursive(NULL,8,20,15,1.5f,1.5f);
	FloorGenListener* listener = new FloorGenListener(this);

	//, border1, inside1);
	bsp.traverseInvertedLevelOrder(&(*listener),NULL);
};

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

void Floor::update() {

	//if there are no entities on this floor then we will simply return
	if(entities.size()==0){
		return;
	}

	//first we attempt to run a creature's turn. On a successful turn, we will
	//push it to the back of the queue and update the game state to reflect that
	if(entities[0]->update(this)){
		entities.push_back(entities[0]);//move next to back of stack
		entities.erase(entities.begin());
		//check if player is the next turn
		if(entities[0]->isPlayer()){
			GameState::setState(STATE_PLAYER_TURN);
		}
		else{
			GameState::setState(STATE_AI_TURN);
		}
	}

}

void Floor::render() {
	for (unsigned int r = 0; r < h; r++) {
		for (unsigned int c = 0; c < w; c++) {
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
	setRectangle(c, r, height, width, outline);

	//Set inside.
	for (unsigned int i = 1; i < height - 1; i++) {
		for (unsigned int k = 1; k < width - 1; k++) {
			setTile(c + k, r + i, TileType(fill));
		}
	}
}

bool Floor::isSolid(unsigned int r, unsigned int c) {
	if(!getTile(r, c).isWalkable()){
		return true;
	}
	return getEntity(c,r)!=nullptr;	//switched because rc to xy
}

Entity* Floor::getEntity(unsigned int x, unsigned int y) {
	for (std::vector<Entity*>::iterator i = entities.begin(); i < entities.end(); i++) {
		if ((*i)->x == x && (*i)->y == y) {
			return *i;
		}
	}

	return nullptr;
}

Entity* Floor::getPlayer(){
	for(int i = 0; i < entities.size(); i++){  //we could use teamPlayer instead
		if(entities[i]->isPlayer()){
			return entities[i];
		}
	}

	//failure state if no player
	return nullptr;
}

unsigned int Floor::getWidth() { return w; }

unsigned int Floor::getHeight() { return h; }

//Explicit instantiations
template void Floor::generateMap<TileNormal>(TileNormal, TileNormal);
template void Floor::generateMap<TileDoor>(TileDoor, TileDoor);

template void Floor::generateFill<TileNormal>(TileNormal);
template void Floor::generateFill<TileDoor>(TileDoor);

template void Floor::setRectangle<TileNormal>(unsigned int, unsigned int, unsigned int, unsigned int, TileNormal, TileNormal);
template void Floor::setRectangle<TileDoor>(unsigned int, unsigned int, unsigned int, unsigned int, TileDoor, TileDoor);

template void Floor::setRectangle<TileNormal>(unsigned int, unsigned int, unsigned int, unsigned int, TileNormal);
template void Floor::setRectangle<TileDoor>(unsigned int, unsigned int, unsigned int, unsigned int, TileDoor);

template void Floor::setTile<TileNormal>(unsigned int, unsigned int, TileNormal);
template void Floor::setTile<TileDoor>(unsigned int, unsigned int, TileDoor);
