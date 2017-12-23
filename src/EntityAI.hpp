#ifndef ENTITYAI
#define ENTITYAI

class EntityAI{

private:
  extern Entity* entity;
public:
  virtual bool isPlayer() = 0;  //to check is is player
  virtual void takeTurn(Map* map) = 0;  //make entity do things
};

#endif
