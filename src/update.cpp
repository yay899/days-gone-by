#include "Engine.hpp"

extern Engine _eng;

void Engine::update() {
	//Code stolen from another one of my projects.
	//Check all events to prevent window from locking up.
	TCOD_key_t key;
	TCOD_mouse_t mouse;
	TCOD_event_t ev = TCODSystem::checkForEvent(TCOD_EVENT_ANY, &key, &mouse);
	//End theft.

	//Check global keys.
	if (ev == TCOD_EVENT_KEY_PRESS) {
		switch (_eng.gameState) {
		case STATE_IN_MENU:
			switch (key.vk) {
			case TCODK_ENTER:
				_eng.openMenus.at(0)->execute(_eng.currentMap);
				_eng.closeMenu();
				if (_eng.openMenus.size() == 0) _eng.gameState = STATE_PLAYER_TURN;
				break;
			case TCODK_UP:
				_eng.openMenus.at(0)->selectUp();
				break;
			case TCODK_DOWN:
				_eng.openMenus.at(0)->selectDown();
				break;
			case TCODK_CHAR:
				_eng.openMenus.at(0)->execute(key.c - 97, _eng.currentMap);
				_eng.closeMenu();
				if (_eng.openMenus.size() == 0) _eng.gameState = STATE_PLAYER_TURN;
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
				_eng.gameState = STATE_IN_MENU;
				break;
			default:
				break;
			}
		}
	}

	//Check gameState dependent keys.
	switch (_eng.gameState) {
	default:
	case STATE_PLAYER_TURN:
	case STATE_AI_TURN:
		//Only pass keycode if it's when the key is pressed, to prevent it from passing key up events.
		if (ev == TCOD_EVENT_KEY_PRESS) {
			_eng.currentMap->update(TCODSystem::getLastFrameLength(), key);
		} else {
			_eng.currentMap->update(TCODSystem::getLastFrameLength(), TCOD_key_t()); //Hopefully this is null and not about to explode.
		}
		break;

	case STATE_IN_MENU:
		break;
	}
}