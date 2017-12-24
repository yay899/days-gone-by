#ifndef ENTITYAI
#define ENTITYAI

#include "Entity.hpp"
#include "Floor.hpp"

class Floor;
class Entity;

class EntityAI{

protected:
  Entity* entity;
public:
  virtual bool isPlayer() = 0;  //to check is is player
  virtual bool takeTurn(Floor* floor) = 0;  //make entity do things
};

#endif
