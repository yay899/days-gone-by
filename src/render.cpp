#include "Engine.hpp"

void Engine::render() {
	TCODConsole::root->clear(); //Clear screen.
	
	//Render current map.
	currentMap->render();
	
	//Render menus so that index 0 is rendered last.
	if (gameState == STATE_IN_MENU) {
		for (std::vector<Menu*>::reverse_iterator i = openMenus.rbegin(); i < openMenus.rend(); i++) {
			(*i)->render(4, 4);
		}
	}

	TCODConsole::root->flush(); //Display buffer on screen.
}