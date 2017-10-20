#include "libtcod.hpp"

int main(int argc, char *argv[]) {

	TCODConsole::initRoot(80, 50, "days-gone-by");

	//Main game loop.
	while (!TCODConsole::isWindowClosed()) { //Note, this doesn't actually do anything yet as the window does not handle inputs--including clicking the x button.

		/*
			Maybe break this this up into two functions or so.
				One for game calculations, like state.update(); or whatever.
				And then the other for rendering state.render(); or something.

			Basically to keep us from constantly needing to change main();
		*/

	}

	return 0;
}