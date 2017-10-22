#include "render.hpp"

void render(Map* map) {
	TCODConsole::root->clear();
	map->render();
	TCODConsole::root->flush();
}