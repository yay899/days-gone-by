#include "PlayerAI.hpp"

PlayerAI::PlayerAI(Entity* ent){
  entity = ent;
}
bool PlayerAI::isPlayer(){
  return true;
}
void PlayerAI::takeTurn(Map* map){
  bool invalid = true;
  while(invalid){
    TCOD_key_t key = getInput();
    invalid=false;

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
      invalid=true;
		  break;
	 }
  }
}
TCOD_key_t getInput(){
  TCOD_key_t key;
	TCOD_mouse_t mouse;
	TCOD_event_t ev = TCODSystem::checkForEvent(TCOD_EVENT_ANY, &key, &mouse);
}
