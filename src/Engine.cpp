#include "Engine.hpp"
#include "InputBuffer.hpp"

Engine::Engine() : Dungeons(std::vector<Dungeon*>()), menus(std::vector<Menu*>()), gameHud(Hud(8)), gameState(STATE_PLAYER_TURN), currentDungeon(nullptr), openMenus(std::vector<Menu*>()) {

}

Engine::~Engine() {
	//Only need to clear these two vectors, as the other two will only contain references to these.
	for (std::vector<Dungeon*>::iterator i = Dungeons.begin(); i < Dungeons.end(); i++) {
		delete *i;
	}
	for (std::vector<Menu*>::iterator i = menus.begin(); i < menus.end(); i++) {
		delete *i;
	}
}

unsigned int Engine::addDungeon(Dungeon* dungeon) {
	Dungeons.push_back(dungeon);
	return (unsigned int)Dungeons.size() - 1;
}

unsigned int Engine::addCurrentDungeon(Dungeon* dungeon) {
	currentDungeon = dungeon;
	Dungeons.push_back(dungeon);
	return (unsigned int)Dungeons.size() - 1;
}

Dungeon* Engine::getDungeon(unsigned int i) {
	return Dungeons.at(i);
}

unsigned int Engine::findDungeon(Dungeon* dungeon) {
	for (unsigned int i = 0; i < Dungeons.size() - 1; i++) {
		if (Dungeons.at(i) == dungeon) return i;
	}

	return -1;
}

void Engine::removeDungeon(unsigned int i) {
	delete Dungeons.at(i);
	Dungeons.erase(Dungeons.begin() + i);
}

unsigned int Engine::addMenu(Menu menu) {
	menus.push_back(new Menu(menu));
	return (unsigned int)menus.size() - 1;
}

Menu* Engine::getMenu(unsigned int i) {
	return menus.at(i);
}

int Engine::findMenu(Menu* menu) {
	for (unsigned int i = 0; i < menus.size() - 1; i++) {
		if (menus.at(i) == menu) return i;
	}

	return -1;
}

void Engine::removeMenu(unsigned int i) {
	delete menus.at(i);
	menus.erase(menus.begin() + i);
}

void Engine::openMenu(unsigned int i) {
	openMenus.insert(openMenus.begin(), menus.at(i));
}

void Engine::closeMenu() {
	openMenus.erase(openMenus.begin());
}

void Engine::render() {
	TCODConsole::root->clear(); //Clear screen.

	//Render current Dungeon.
	currentDungeon->currentFloor->render();

	//Render menus so that index 0 is rendered last.
	if (gameState == STATE_IN_MENU) {
		for (std::vector<Menu *>::reverse_iterator i = openMenus.rbegin(); i < openMenus.rend(); i++) {
			(*i)->render(4, 4);
		}
	}

	gameHud.render();

	TCODConsole::root->flush(); //Display buffer on screen.
}

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
						openMenus.at(0)->execute(currentDungeon->currentFloor);
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
						openMenus.at(0)->execute(key.c - 97, currentDungeon->currentFloor);
						closeMenu();
						if (openMenus.size() == 0) gameState = STATE_PLAYER_TURN;
						break;
					default:
						break;
				}
				break;

			case STATE_PLAYER_TURN:
			case STATE_AI_TURN:
				//HERE
				KBBuffer::getInstance()->addKey(key);
				//HERE
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
			//HERE-> //nope this is going to be alright for now
			currentDungeon->currentFloor->update();
			//HERE->
			break;

		case STATE_IN_MENU:
			break;
	}

	gameHud.update();
}