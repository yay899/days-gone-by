#include "update.hpp"

extern State _gameState;
extern Menu _menu;

void update(Map* map) {
	//Code stolen from another one of my projects.
	//Check all events to prevent window from locking up.
	TCOD_key_t key;
	TCOD_mouse_t mouse;
	TCOD_event_t ev = TCODSystem::checkForEvent(TCOD_EVENT_ANY, &key, &mouse);
	//End theft.

	/*
		Test code.
	*/
	if (ev == TCOD_EVENT_KEY_PRESS && key.vk == TCODK_ESCAPE) {
		_menu = Menu("BLAH");
		_menu.options.push_back(std::tuple<std::string, void(*)(Map*)>("TEST OPTION", &Menu::testOption));
		_menu.options.push_back(std::tuple<std::string, void(*)(Map*)>("TEST OPTION 2", &Menu::testOption));
		_menu.options.push_back(std::tuple<std::string, void(*)(Map*)>("AAAAAAAAAAAAAAAAAAAAAAAAa", &Menu::testOption));
		_gameState = STATE_IN_MENU;
	}
	/*
		End test code.
	*/

	switch (_gameState) {
	default:
	case STATE_PLAYER_TURN:
	case STATE_AI_TURN:
		//Only pass keycode if it's when the key is pressed, to prevent it from passing key up events.
		if (ev == TCOD_EVENT_KEY_PRESS) {
			map->update(TCODSystem::getLastFrameLength(), key);
		}
		else {
			map->update(TCODSystem::getLastFrameLength(), TCOD_key_t()); //Hopefully this is null and not about to explode.
		}
		break;

	case STATE_IN_MENU:
		if (ev == TCOD_EVENT_KEY_PRESS) {
			switch (key.vk) {
			case TCODK_ENTER:
				_menu.execute(map);
				_gameState = STATE_PLAYER_TURN;
				break;
			case TCODK_UP:
				_menu.selectUp();
				break;
			case TCODK_DOWN:
				_menu.selectDown();
				break;
			case TCODK_CHAR:
				_menu.execute(key.c - 97, map);
				_gameState = STATE_PLAYER_TURN;
				break;
			default:
				break;
			}
		}
		break;
	}
}