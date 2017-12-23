#ifndef PLAYERAI
#define PLAYERAI

class PlayerAI{

private:
  Entity* entity;
public:
  PlayerAI(Entity* ent);
  bool isPlayer();
  void takeTurn(Map* map);
  TCOD_key_t getInput();

};
