#include "PlayerAI.hpp"
#include "InputBuffer.hpp"
#include "Engine.hpp"

#include <iostream>

PlayerAI::PlayerAI(Entity* ent){
  entity = ent;
}
bool PlayerAI::isPlayer(){
  return true;
}
bool PlayerAI::takeTurn(Floor* floor){
		TCOD_key_t key;
		switch(GameState::getState()){
		case STATE_PLAYER_TURN:

    key = getInput();

    switch (key.vk) {
	   //Characters.
	   case TCODK_CHAR:
		  switch (key.c) {
				case 'e':
					GameState::setState(STATE_CHOOSING_DIRECTION);
					return false;
		    case '.':
					return true;
		    default:
			  	return false;
		  }
		  break;
	   //Special keys.
	   case TCODK_UP:
		  entity->move(entity->x, entity->y - 1, floor);
		  break;
	   case TCODK_DOWN:
		  entity->move(entity->x, entity->y + 1, floor);
		  break;
	   case TCODK_LEFT:
		  entity->move(entity->x - 1, entity->y, floor);
		  break;
	   case TCODK_RIGHT:
		  entity->move(entity->x + 1, entity->y, floor);
		  break;
	   case TCODK_KP1:
		  entity->move(entity->x - 1, entity->y + 1, floor);
		  break;
	   case TCODK_KP2:
		  entity->move(entity->x, entity->y + 1, floor);
		  break;
	   case TCODK_KP3:
		  entity->move(entity->x + 1, entity->y + 1, floor);
		  break;
	   case TCODK_KP4:
		  entity->move(entity->x - 1, entity->y, floor);
		  break;
	   case TCODK_KP5:
		  break;
	   case TCODK_KP6:
		  entity->move(entity->x + 1, entity->y, floor);
		  break;
	   case TCODK_KP7:
		  entity->move(entity->x - 1, entity->y - 1, floor);
		  break;
	   case TCODK_KP8:
		  entity->move(entity->x, entity->y - 1, floor);
		  break;
	   case TCODK_KP9:
		  entity->move(entity->x + 1, entity->y - 1, floor);
		  break;
	   default:
      return false;
		  break;
	 }
   return true;

	 case STATE_CHOOSING_DIRECTION:
	 key = getInput();

	 switch (key.vk) {
		//Special keys.
		case TCODK_UP:
		 entity->interact(entity->x, entity->y - 1, floor);
		 break;
		case TCODK_DOWN:
		 entity->interact(entity->x, entity->y + 1, floor);
		 break;
		case TCODK_LEFT:
		 entity->interact(entity->x - 1, entity->y, floor);
		 break;
		case TCODK_RIGHT:
		 entity->interact(entity->x + 1, entity->y, floor);
		 break;
		case TCODK_KP1:
		 entity->interact(entity->x - 1, entity->y + 1, floor);
		 break;
		case TCODK_KP2:
		 entity->interact(entity->x, entity->y + 1, floor);
		 break;
		case TCODK_KP3:
		 entity->interact(entity->x + 1, entity->y + 1, floor);
		 break;
		case TCODK_KP4:
		 entity->interact(entity->x - 1, entity->y, floor);
		 break;
		case TCODK_KP5:
		 break;
		case TCODK_KP6:
		 entity->interact(entity->x + 1, entity->y, floor);
		 break;
		case TCODK_KP7:
		 entity->interact(entity->x - 1, entity->y - 1, floor);
		 break;
		case TCODK_KP8:
		 entity->interact(entity->x, entity->y - 1, floor);
		 break;
		case TCODK_KP9:
		 entity->interact(entity->x + 1, entity->y - 1, floor);
		 break;
		default:
		 return false;
		 break;
	}
		return true;
	}
}
TCOD_key_t PlayerAI::getInput(){
  return KBBuffer::getInstance()->nextKey();
}
