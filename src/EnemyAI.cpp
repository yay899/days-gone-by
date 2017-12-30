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
      return false;
    }

  }

  return true;
}
