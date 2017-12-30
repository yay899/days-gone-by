#include "libtcod.hpp"
#include "Floor.hpp"
#include "Menu.hpp"
#include "Engine.hpp"
#include <iostream>

Engine _eng = Engine();

/*
	Constants
*/
const unsigned int SCREEN_WIDTH = 88;
const unsigned int SCREEN_HEIGHT = 50;

int main(int argc, char *argv[]) {
	//Initialization
	TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "days-gone-by");

	//Move these eventually.
	{
		Floor *temp = new Floor(80, 50);
        Dungeon *tempDun = new Dungeon();
        tempDun->addCurrentFloor(temp);		temp->generateFill(TileNormal(' ', TCOD_white, TCOD_black, true, false, true));
		//temp->setRectangle(10, 10, 7, 7, TileNormal('#', TCOD_white, TCOD_black, true, false, true), TileNormal('.', TCOD_white, TCOD_black, true, false, false));
		//temp->setRectangle(15, 15, 10, 10, TileNormal('#', TCOD_white, TCOD_black, true, false, true), TileNormal('.', TCOD_white, TCOD_black, true, false, false));
		temp->generateMap(TileNormal('#', TCOD_white, TCOD_black, true, false, true), TileNormal('.', TCOD_white, TCOD_black, true, false, false));
		_eng.addCurrentDungeon(tempDun);
	}


	{
		Menu temp = Menu("ESC");
		temp.options.push_back(std::tuple < std::string, void(*)(Floor * ) > ("Create player", &Menu::debugAddPlayer));

		temp.options.push_back(std::tuple < std::string, void(*)(Floor * ) > ("Create test enemy", &Menu::debugAddTestEnemy));

		temp.options.push_back(std::tuple < std::string, void(*)(Floor * ) > ("Highlight solid tiles", &Menu::debugHighlightSolid));

		temp.options.push_back(std::tuple < std::string, void(*)(Floor * ) > ("Exit game", &Menu::exitGame));

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
