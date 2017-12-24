#include "EnemyAI.hpp"

EnemyAI::EnemyAI(Entity* ent){
  entity = ent;
}
bool EnemyAI::isPlayer(){
  return false;
}
bool EnemyAI::takeTurn(Floor* floor){
  //this needs to be implemented
  return true;
}
