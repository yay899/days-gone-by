#include "Engine.hpp"

Engine::Engine() : gameState(STATE_PLAYER_TURN), maps(std::vector<Map*>()), currentMap(nullptr), menus(std::vector<Menu*>()), openMenus(std::vector<Menu*>()) {

}

Engine::~Engine() {
	//Only need to clear tese two vectors, as the other two will only contain references to these.
	for (std::vector<Map*>::iterator i = maps.begin(); i < maps.end(); i++) {
		delete *i;
	}
	for (std::vector<Menu*>::iterator i = menus.begin(); i < menus.end(); i++) {
		delete *i;
	}
}