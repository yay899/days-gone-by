#ifndef ENTITYAI
#define ENTITYAI

class Map;
class Entity;
#include "Entity.hpp"
#include "Map.hpp"

class EntityAI{

protected:
  Entity* entity;
public:
  virtual bool isPlayer() = 0;  //to check is is player
  virtual void takeTurn(Map* map) = 0;  //make entity do things
};

#endif
