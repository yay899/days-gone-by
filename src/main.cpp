#include "libtcod.hpp"
#include "Map.hpp"
#include "Menu.hpp"
#include "Engine.hpp"
#include <iostream>

Engine _eng = Engine();

/*
	Constants
*/
const unsigned int SCREEN_WIDTH = 80;
const unsigned int SCREEN_HEIGHT = 50;

int main(int argc, char *argv[]) {
	//Initialization
	TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "days-gone-by");

	//Move these eventually.
	{
		Map *temp = new Map(80, 50);
		temp->generateFill(TileNormal(' ', TCOD_white, TCOD_black, true, false, true));
		temp->setRectangle(30, 30, 10, 10,TileNormal(' ', TCOD_white, TCOD_black, true, false, true), TileNormal('#', TCOD_white, TCOD_black, true, false, false));
		_eng.addCurrentMap(temp);
	}


	{
		Menu temp = Menu("ESC");
		temp.options.push_back(std::tuple < std::string, void(*)(Map * ) > ("Create player", &Menu::debugAddPlayer));
		temp.options.push_back(std::tuple < std::string, void(*)(Map * ) >
		("Create test enemy", &Menu::debugAddTestEnemy));
		temp.options.push_back(std::tuple < std::string, void(*)(Map * ) >
		("Highlight solid tiles", &Menu::debugHighlightSolid));

		_eng.addMenu(temp);
	}

	{
		//Main game loop.
		while (!TCODConsole::isWindowClosed()) {

			_eng.update();
			_eng.render();

		}
	}

	return 0;
}
