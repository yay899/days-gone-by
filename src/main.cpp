#include "libtcod.hpp"
#include "Map.hpp"
#include "update.hpp"
#include "render.hpp"

int main(int argc, char *argv[]) {

	TCODConsole::initRoot(80, 50, "days-gone-by");

	Map map(80, 50);

	//Main game loop.
	while (!TCODConsole::isWindowClosed()) { //Note, this doesn't actually do anything yet as the window does not handle inputs--including clicking the x button.

		update(&map);
		render(&map);

	}

	return 0;
}