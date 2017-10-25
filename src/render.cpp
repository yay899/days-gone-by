#include "render.hpp"

extern State _gameState;
extern Menu _menu;

void render(Map* map) {
	TCODConsole::root->clear();
	map->render();
	if (_gameState == STATE_IN_MENU) _menu.render(4, 4);
	TCODConsole::root->flush();
}