#include "EmenyAI.hpp"

EnemyAI::EnemyAI(Entity* ent){
  entity = ent;
}
bool EnemyAI::isPlayer(){
  return false;
}
void EnemyAI::takeTurn(Map* map){
  //this needs to be implemented
}
