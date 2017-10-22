#include "libtcod.hpp"
#include "Map.hpp"
#include "update.hpp"
#include "render.hpp"

int main(int argc, char *argv[]) {

	TCODConsole::initRoot(80, 50, "days-gone-by");

	Map map(80, 50);

	//Main game loop.
	while (!TCODConsole::isWindowClosed()) {

		update(&map);
		render(&map);

	}

	return 0;
}