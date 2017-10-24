#include "Menu.hpp"

Menu::Menu() : options(std::vector<std::tuple<std::string, void (*)(Map*)>>()), index(0) {

}

void Menu::render(int x, int y) {

}

void Menu::execute() {

}

void Menu::execute(int i, Map* map) {
	std::get<1>(options.at(i))(map);
}

void Menu::selectUp() {

}

void Menu::selectDown() {

}

void Menu::select(int i) {

}

	/*--------------------------------------------------
					EFFECTS
	--------------------------------------------------*/

void Menu::testOption(Map* map) {

}