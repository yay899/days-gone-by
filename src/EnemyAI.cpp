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
    int diffx = target->x - entity->x;
    int diffy = target->y - entity->y;

    //find best greedy direction to get to target
    if(diffx!=0){
      diffx = diffx / abs(diffx);
    }
    if(diffy!=0){
      diffy = diffy / abs(diffy);
    }

    //move to space
    entity->move(entity->x+diffx,entity->y+diffy,floor);

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

void EnemyAI::pathMove(Floor* floor, int destX, int destY){
	TCOD_map_t map;
	map = TCOD_map_new(floor->getWidth(),floor->getHeight());
	for(int i=0; i<floor->getWidth(); i++){
		for (int p=0; p<floor->getHeight(); p++){
			Tile& tile = floor->getTile(i,p);
			TCOD_map_set_properties(map,i,p,true,floor->getTile(i,p).isWalkable());
		}
	}

	TCOD_path_t path = TCOD_path_new_using_map(map,1.41f);
	TCOD_path_compute(path,entity->x,entity->y,destX,destY);

	int nextX;
	int nextY;
	TCOD_path_get(path,0,&nextX,&nextY);

	TCOD_path_delete(path);

	entity->move(nextX,nextY,floor);

}
