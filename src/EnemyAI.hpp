#ifndef ENEMYAI
#define EMENYAI

#include "Entity.hpp"
#include "Map.hpp"

class EnemyAI:public EntityAI{

public:
  EnemyAI(Entity* ent);
  bool isPlayer();
  bool takeTurn(Map* map);

};

#endif
