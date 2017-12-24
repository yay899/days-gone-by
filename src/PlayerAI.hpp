#ifndef PLAYERAI
#define PLAYERAI

#include "Entity.hpp"
#include "Floor.hpp"

class PlayerAI:public EntityAI{

public:
  PlayerAI(Entity* ent);
  bool isPlayer();
  bool takeTurn(Floor* floor);
  TCOD_key_t getInput();

};

#endif
