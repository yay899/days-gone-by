#include "EnemyAI.hpp"
#include <stddef.h>

EnemyAI::EnemyAI(Entity* ent){
  entity = ent;
}
bool EnemyAI::isPlayer(){
  return false;
}
bool EnemyAI::takeTurn(Floor* floor){

  //check for a target
  if(target!=nullptr){
    //calcuate vector to target
    int destX = target->x;
    int destY = target->y;
		pathMove(destX,destY,floor);

		return true;
  }
  else{
    //find a target
    target = floor->getPlayer();

    if(target!=nullptr){
      return false;
      //if we found a target lets take a turn.
    }
    else{
      //if still no target, don't freeze the game thinking forever.
      return true;
    }

  }

  return true;
}

bool EnemyAI::pathMove(int destX, int destY, Floor* floor){
	TCOD_map_t map;
	int H = floor->getHeight();
	int W = floor->getWidth();
	map = TCOD_map_new(W,H);

	for(int i=0; i<H; i++){
		for (int p=0; p<W; p++){
			Tile& tile = floor->getTile(i,p);
			TCOD_map_set_properties(map,p,i,true,floor->getTile(i,p).isWalkable());
		}
	}

	TCOD_path_t path = TCOD_path_new_using_map(map,1.41f);
	TCOD_path_compute(path,entity->x,entity->y,destX,destY);

	int nextX;
	int nextY;
	if(TCOD_path_size(path)==0){	//check validity
		return false;
	}
	TCOD_path_get(path,0,&nextX,&nextY);
	TCOD_path_delete(path);

	entity->move(nextX,nextY,floor);
	return true;
}
