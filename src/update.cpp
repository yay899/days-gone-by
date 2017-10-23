#include "update.hpp"

void update(Map* map) {
	//Code stolen from another one of my projects.
	//Check all events to prevent window from locking up.
	TCOD_key_t key;
	TCOD_mouse_t mouse;
	TCOD_event_t ev = TCODSystem::checkForEvent(TCOD_EVENT_ANY, &key, &mouse);
	//End theft.

	//Only pass keycode if it's when the key is pressed, to prevent it from passing key up events.
	if (ev == TCOD_EVENT_KEY_PRESS) {
		map->update(TCODSystem::getLastFrameLength(), key);
	}
	else {
		map->update(TCODSystem::getLastFrameLength(), TCOD_key_t()); //Hopefully this is null and not about to explode.
	}
}