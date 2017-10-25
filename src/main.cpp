#include "libtcod.hpp"
#include "Map.hpp"
#include "update.hpp"
#include "render.hpp"
#include "Menu.hpp"

State _gameState = STATE_PLAYER_TURN;
Menu _menu = Menu(); //TODO figure out how to not use a global here.

int main(int argc, char *argv[]) {

	TCODConsole::initRoot(80, 50, "days-gone-by");

	Map map(50, 80);

	//Main game loop.
	while (!TCODConsole::isWindowClosed()) {

		update(&map);
		render(&map);

	}

	return 0;
}