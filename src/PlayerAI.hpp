#ifndef PLAYERAI
#define PLAYERAI

#include "Entity.hpp"
#include "Map.hpp"

class PlayerAI:public EntityAI{

public:
  PlayerAI(Entity* ent);
  bool isPlayer();
  void takeTurn(Map* map);
  TCOD_key_t getInput();

};

#endif
