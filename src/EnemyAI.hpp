#ifndef PLAYERAI
#define PLAYERAI

class EnemyAI{

private:
  Entity* entity;
public:
  EnemyAI(Entity* ent);
  bool isPlayer();
  void takeTurn(Map* map);

};
