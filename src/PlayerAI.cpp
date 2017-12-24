#include "PlayerAI.hpp"
#include "InputBuffer.hpp"

#include <iostream>

PlayerAI::PlayerAI(Entity* ent){
  entity = ent;
}
bool PlayerAI::isPlayer(){
  return true;
}
bool PlayerAI::takeTurn(Map* map){
    TCOD_key_t key = getInput();

    switch (key.vk) {
	   //Characters.
	   case TCODK_CHAR:
		  switch (key.c) {
		    case '.':
		    default:
			     break;
		  }
		  break;
	   //Special keys.
	   case TCODK_UP:
		  entity->move(entity->x, entity->y - 1, map);
		  break;
	   case TCODK_DOWN:
		  entity->move(entity->x, entity->y + 1, map);
		  break;
	   case TCODK_LEFT:
		  entity->move(entity->x - 1, entity->y, map);
		  break;
	   case TCODK_RIGHT:
		  entity->move(entity->x + 1, entity->y, map);
		  break;
	   case TCODK_KP1:
		  entity->move(entity->x - 1, entity->y + 1, map);
		  break;
	   case TCODK_KP2:
		  entity->move(entity->x, entity->y + 1, map);
		  break;
	   case TCODK_KP3:
		  entity->move(entity->x + 1, entity->y + 1, map);
		  break;
	   case TCODK_KP4:
		  entity->move(entity->x - 1, entity->y, map);
		  break;
	   case TCODK_KP5:
		  break;
	   case TCODK_KP6:
		  entity->move(entity->x + 1, entity->y, map);
		  break;
	   case TCODK_KP7:
		  entity->move(entity->x - 1, entity->y - 1, map);
		  break;
	   case TCODK_KP8:
		  entity->move(entity->x, entity->y - 1, map);
		  break;
	   case TCODK_KP9:
		  entity->move(entity->x + 1, entity->y - 1, map);
		  break;
	   default:
      return false;
		  break;
	 }
   return true;
}
TCOD_key_t PlayerAI::getInput(){
  return KBBuffer::getInstance()->nextKey();
}
