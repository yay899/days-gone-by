#include "Engine.hpp"

void Engine::update() {
	//Code stolen from another one of my projects.
	//Check all events to prevent window from locking up.
	TCOD_key_t key;
	TCOD_mouse_t mouse;
	TCOD_event_t ev = TCODSystem::checkForEvent(TCOD_EVENT_ANY, &key, &mouse);
	//End theft.

	//Check global keys.
	if (ev == TCOD_EVENT_KEY_PRESS) {
		switch (gameState) {
		case STATE_IN_MENU:
			switch (key.vk) {
			case TCODK_ENTER:
				openMenus.at(0)->execute(currentMap);
				closeMenu();
				if (openMenus.size() == 0) gameState = STATE_PLAYER_TURN;
				break;
			case TCODK_UP:
				openMenus.at(0)->selectUp();
				break;
			case TCODK_DOWN:
				openMenus.at(0)->selectDown();
				break;
			case TCODK_CHAR:
				openMenus.at(0)->execute(key.c - 97, currentMap);
				closeMenu();
				if (openMenus.size() == 0) gameState = STATE_PLAYER_TURN;
				break;
			default:
				break;
			}
			break;

		case STATE_PLAYER_TURN:
		case STATE_AI_TURN:
		default:
			switch (key.vk) {
			case TCODK_ESCAPE:
				openMenu(0);
				gameState = STATE_IN_MENU;
				break;
			default:
				break;
			}
		}
	}

	//Check gameState dependent keys.
	switch (gameState) {
	default:
	case STATE_PLAYER_TURN:
	case STATE_AI_TURN:
		//Only pass keycode if it's when the key is pressed, to prevent it from passing key up events.
		if (ev == TCOD_EVENT_KEY_PRESS) {
			currentMap->update(TCODSystem::getLastFrameLength(), key);
		} else {
			currentMap->update(TCODSystem::getLastFrameLength(), TCOD_key_t()); //Hopefully this is null and not about to explode.
		}
		break;

	case STATE_IN_MENU:
		break;
	}

	gameHud.update();
}