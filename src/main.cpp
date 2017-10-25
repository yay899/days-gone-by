#include "libtcod.hpp"
#include "Map.hpp"
#include "Menu.hpp"
#include "Engine.hpp"

Engine _eng = Engine();

int main(int argc, char *argv[]) {
	//Initialization
	TCODConsole::initRoot(80, 50, "days-gone-by");

	//Move these eventually.
	{
		Map* temp = new Map(50, 80);
		temp->generateFill(Tile(' '));

		_eng.addCurrentMap(temp);
	}

	{
		Menu temp = Menu("ESC");
		temp.options.push_back(std::tuple<std::string, void(*)(Map*)>("Create player", &Menu::testOption));
		temp.options.push_back(std::tuple<std::string, void(*)(Map*)>("Create test enemy", &Menu::testOption2));

		_eng.addMenu(temp);
	}

	//Main game loop.
	while (!TCODConsole::isWindowClosed()) {

		_eng.update();
		_eng.render();

	}

	return 0;
}