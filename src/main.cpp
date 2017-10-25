#include "libtcod.hpp"
#include "Map.hpp"
#include "Menu.hpp"
#include "Engine.hpp"

Engine _eng = Engine();
State _gameState = STATE_PLAYER_TURN;
Menu _menu = Menu("BLAH"); //TODO figure out how to not use a global here.

int main(int argc, char *argv[]) {

	TCODConsole::initRoot(80, 50, "days-gone-by");

	Map* map = new Map(50, 80);
	_eng.maps.push_back(map);
	_eng.currentMap = map;

	//Main game loop.
	while (!TCODConsole::isWindowClosed()) {

		_eng.update(_eng.currentMap);
		_eng.render(_eng.currentMap);

	}

	return 0;
}