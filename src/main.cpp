#include "libtcod.hpp"
#include "Floor.hpp"
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
		Floor *temp = new Floor(80, 50);
        Dungeon *tempDun = new Dungeon();
        tempDun->addCurrentFloor(temp);		temp->generateFill(TileNormal(' ', TCOD_white, TCOD_black, true, false, true));
		temp->setLine(10, 10, 40, 15, TileNormal('#', TCOD_white, TCOD_black, true, false, false), TileNormal('.', TCOD_white, TCOD_black, true, false, true));
		_eng.addCurrentDungeon(tempDun);
	}


	{
		Menu temp = Menu("ESC");
		temp.options.push_back(std::tuple < std::string, void(*)(Floor * ) > ("Create player", &Menu::debugAddPlayer));
		temp.options.push_back(std::tuple < std::string, void(*)(Floor * ) >
		("Create test enemy", &Menu::debugAddTestEnemy));
		temp.options.push_back(std::tuple < std::string, void(*)(Floor * ) >
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
