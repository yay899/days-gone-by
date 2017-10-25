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

unsigned int Engine::addMap(Map* map) {
	maps.push_back(map);
	return maps.size() - 1;
}

unsigned int Engine::addCurrentMap(Map* map) {
	currentMap = map;
	maps.push_back(map);
	return maps.size() - 1;
}

Map* Engine::getMap(unsigned int i) {
	return maps.at(i);
}

int Engine::findMap(Map* map) {
	for (unsigned int i = 0; i < maps.size() - 1; i++) {
		if (maps.at(i) == map) return i;
	}

	return -1;
}

void Engine::removeMap(unsigned int i) {
	delete maps.at(i);
	maps.erase(maps.begin() + i);
}

unsigned int Engine::addMenu(Menu menu) {
	menus.push_back(new Menu(menu));
	return maps.size() - 1;
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