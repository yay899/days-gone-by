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
	void pathMove(Floor*,int,int);

};

#endif
