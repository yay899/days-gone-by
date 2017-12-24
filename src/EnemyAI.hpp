#ifndef ENEMYAI
#define EMENYAI

#include "Entity.hpp"
#include "Floor.hpp"

class EnemyAI:public EntityAI{

public:
  EnemyAI(Entity* ent);
  bool isPlayer();
  bool takeTurn(Floor* floor);

};

#endif
