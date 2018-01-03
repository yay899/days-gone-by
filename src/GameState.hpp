#ifndef GAMESTATE
#define GAMESTATE


#include <stddef.h>

enum State {
	STATE_PLAYER_TURN,
	STATE_CHOOSING_DIRECTION,
	STATE_AI_TURN,
	STATE_IN_MENU
};

class GameState{
public:
  static GameState* getInstance();
  static State getState();
  static void setState(State);
private:
  static State gameState;

  GameState(){
  };
  GameState(GameState const&){
  };
  GameState& operator = (GameState const&);
  static GameState* gs;

};

#endif
