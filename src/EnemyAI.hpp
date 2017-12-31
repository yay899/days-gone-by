#ifndef ENEMYAI
#define ENEMYAI

#include "Entity.hpp"
#include "Floor.hpp"

class EnemyAI:public EntityAI{

public:
  EnemyAI(Entity* ent);
  bool isPlayer();
  bool takeTurn(Floor* floor);

private:
  Entity* target;
	bool pathMove(int,int,Floor*);

};

#endif
