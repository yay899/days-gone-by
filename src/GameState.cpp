#include "GameState.hpp"
#include <stddef.h>

GameState* GameState::gs = nullptr;
State GameState::gameState = STATE_PLAYER_TURN;

GameState* GameState::getInstance(){
  if(gs==nullptr){
    gs = new GameState;
	}
  return gs;
}
/*GameState::~GameState(){
}*/
State GameState::getState(){
	return GameState::gameState;
}
void GameState::setState(State state){
	GameState::gameState = state;
}
