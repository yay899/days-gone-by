#include "Floor.hpp"

#include "Engine.hpp"
#include "FloorGenListener.hpp"
#include <iostream>


int* Floor::generateMap(){
	TCODBsp bsp(0,0,w,h);
	bsp.splitRecursive(NULL,8,20,15,1.5f,1.5f);
	FloorGenListener* listener = new FloorGenListener(this);

	//, border1, inside1);
	bsp.traverseInvertedLevelOrder(&(*listener),NULL);
	int * coords = new int[2];
	coords[0] = listener->lastRoomX;
	coords[1] = listener->lastRoomY;
	return coords;
}

Floor::Floor(unsigned int w, unsigned int h) : w(w), h(h), sightMap(TCODMap(w, h)) {
	tileMap = new Tile**[w];
    for(unsigned int i = 0; i < w; i++) {
		tileMap[i] = new Tile*[h];
	}


	for (unsigned int  y = 0; y < h; y++) {
		for (unsigned int x = 0; x < w; x++) {
			tileMap[x][y] = new TileNormal();
		}
	}
}

Floor::~Floor() {
	for (unsigned int  i= 0; i < w; i++) {
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
	for (unsigned int y = 0; y < h; y++) {
		for (unsigned int x = 0; x < w; x++) {
			getTile(x, y).render(x, y);
		}
	}

	for (std::vector<Entity*>::iterator i = entities.begin(); i < entities.end(); i++) {
		(*i)->render();
	}
}

void Floor::addEntity(Entity* e) {
	entities.emplace_back(e);
}

template <class TileType>
void Floor::generateFill(TileType t) {
	for (unsigned int  y = 0; y < h; y++) {
		for (unsigned int x = 0; x < w; x++) {
			delete tileMap[x][y];
			tileMap[x][y] = new TileType(t);
		}
	}
}

Tile& Floor::getTile(unsigned int x, unsigned int y) {//here DONE
	return *tileMap[x][y];
}

template <class TileType>
void Floor::setTile(unsigned int x, unsigned int y, TileType t) {
	delete tileMap[x][y];
	tileMap[x][y] = new TileType(t);
}

template <class TileType>
void Floor::setRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height, TileType outline) {//here DONE

	//Draw horizontal portion of outline.
	for (unsigned int i = 0; i < width; i++) {
		setTile(x + i, y, TileType(outline));
		setTile( x + i, y + height - 1, TileType(outline));
	}

	//Draw vertical portion of outline.
	for (unsigned int i = 1; i < height - 1; i++) { //Start and end one early because the horizontal already covered the corners.
		setTile(x, y + i, TileType(outline));
		setTile(x + width - 1, y + i, TileType(outline));
	}
}

template <class TileType>
void Floor::setRectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height, TileType outline, TileType fill) {//here DONE
	//Set outline.
	//setRectangle(x, y, width, height, outline);

	//Set inside.
	for (unsigned int i = 1; i < height - 1; i++) {
		for (unsigned int k = 1; k < width - 1; k++) {
			setTile(x + k, y + i, TileType(fill));
		}
	}
}

bool Floor::isSolid(unsigned int x, unsigned int y) {//here DONE
	if(!getTile(x, y).isWalkable()){
		return true;
	}
	return getEntity(x,y)!=nullptr;	//switched because rc to xy
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

void Floor::updateSightMap() {
	for (unsigned int x = 0; x < w; x++) {
		for (unsigned int y = 0; y < h; y++) {
			sightMap.setProperties(x, y, getTile(x, y).isClear(), false);
		}
	}
}

void Floor::updateSight(Entity& e) {
	sightMap.computeFov(e.x, e.y);

	for (unsigned int x = 0; x < w; x++) {
		for (unsigned int y = 0; y < h; y++) {
			if (sightMap.isInFov(x, y)) {
				getTile(x, y).setSeen(SEEING);
			} else {
				getTile(x, y).setSeen(getTile(x, y).getSeen == SEEING ? SEEN : UNSEEN);
			}
		}
	}
}

//Explicit instantiations

template void Floor::generateFill<TileNormal>(TileNormal);
template void Floor::generateFill<TileDoor>(TileDoor);

template void Floor::setRectangle<TileNormal>(unsigned int, unsigned int, unsigned int, unsigned int, TileNormal, TileNormal);
template void Floor::setRectangle<TileDoor>(unsigned int, unsigned int, unsigned int, unsigned int, TileDoor, TileDoor);

template void Floor::setRectangle<TileNormal>(unsigned int, unsigned int, unsigned int, unsigned int, TileNormal);
template void Floor::setRectangle<TileDoor>(unsigned int, unsigned int, unsigned int, unsigned int, TileDoor);

template void Floor::setTile<TileNormal>(unsigned int, unsigned int, TileNormal);
template void Floor::setTile<TileDoor>(unsigned int, unsigned int, TileDoor);
