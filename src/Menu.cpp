#include "Menu.hpp"

Menu::Menu(std::string name) : options(std::vector<std::tuple<std::string, void (*)(Map*)>>()), index(0), name(name) {

}

void Menu::render(int x, int y) {
	//Calculate size box needs to be.
	unsigned int height = options.size();
	unsigned int width = 0;
	for (std::vector<std::tuple<std::string, void(*)(Map*)>>::iterator i = options.begin(); i < options.end(); i++) {
		if (std::get<0>(*i).length() > width) width = std::get<0>(*i).length();
	}

	//Expand box for padding, plus markers on left side of options.
	height += 4;
	width += 6;
	width = MAX(width, name.length() + 4);

	//Store old default colors and set new ones.
	TCODColor oldBackground = TCODConsole::root->getDefaultBackground();
	TCODColor oldForeground = TCODConsole::root->getDefaultForeground();
	TCOD_bkgnd_flag_t oldFlag = TCODConsole::root->getBackgroundFlag();
	TCOD_alignment_t oldAlignment = TCODConsole::root->getAlignment();
	TCODConsole::root->setDefaultBackground(MENU_BACKGROUND);
	TCODConsole::root->setDefaultForeground(MENU_FOREGROUND);
	TCODConsole::root->setBackgroundFlag(TCOD_BKGND_SET);
	TCODConsole::root->setAlignment(TCOD_LEFT);

	//Wrote this before I found out printFrame was a function. :c
	//This is why you always read *all* of the documentation.
	/*
	//Draw box.
	for (int ix = x; ix < x + width; ix++) TCODConsole::root->setChar(ix, y, '-');
	for (int ix = x; ix < x + width; ix++) TCODConsole::root->setChar(ix, y + height, '-');
	for (int iy = y; iy < y + height; iy++) TCODConsole::root->setChar(x, iy, '|');
	for (int iy = y; iy < y + height; iy++) TCODConsole::root->setChar(x + width, iy, '|');

	//Draw corners.
	TCODConsole::root->setChar(x, y, '+');
	TCODConsole::root->setChar(x + width, y, '+');
	TCODConsole::root->setChar(x, y + height, '+');
	TCODConsole::root->setChar(x + width, y + height, '+');
	*/

	TCODConsole::root->printFrame(x, y, width, height, true, TCOD_BKGND_DEFAULT, name.c_str());

	//Draw options.
	std::string s = ""; //For some reason this as to be declared out here or else it'll drop out of scope when TCODConsole tries to print it????
	for (unsigned int i = 0; i < options.size(); i++) {
		s = "";
		s += (char)(i + 97); //97 is important. It offsets it to the beginning of letters.
		s += '-';
		s += std::get<0>(options.at(i));
		
		if (index == i) TCODConsole::root->setDefaultForeground(MENU_SELECT_FOREGROUND); //Highlight selection.
		TCODConsole::root->print(x + 2, y + 2 + i, s.c_str());
		if (index == i) TCODConsole::root->setDefaultForeground(MENU_FOREGROUND);
	}
	
	//Highlight selection.
	TCODConsole::root->setDefaultBackground(MENU_SELECT_BACKGROUND);
	TCODConsole::root->rect(x + 1, y + index + 2, width - 2, 1, false);

	//Restore default colors.
	TCODConsole::root->setDefaultBackground(oldBackground);
	TCODConsole::root->setDefaultForeground(oldForeground);
	TCODConsole::root->setBackgroundFlag(oldFlag);
	TCODConsole::root->setAlignment(oldAlignment);
}

void Menu::execute(Map* map) {
	std::get<1>(options.at(index))(map);
}

void Menu::execute(unsigned int i, Map* map) {
	if (i <= options.size()) std::get<1>(options.at(i))(map);
}

void Menu::selectUp() {
	if (index > 0) index--;
}

void Menu::selectDown() {
	if (index < options.size() - 1) index++;
}

void Menu::select(unsigned int i) {
	if (i <= options.size()) index = i;
}

	/*--------------------------------------------------
					EFFECTS
	--------------------------------------------------*/

void Menu::debugAddPlayer(Map* map) {
	map->addTeamPlayer(new EntityPlayer(0, 0, '@'));
}

void Menu::debugAddTestEnemy(Map* map) {
	map->addTeamAI(new EntityTestEnemy(map->getWidth(), map->getHeight(), 'e'));
}

void Menu::debugHighlightSolid(Map* map) {
	for (unsigned int x = 0; x < map->getWidth(); x++) {
		for (unsigned int y = 0; y < map->getHeight(); y++) {
			if (map->isSolid(x, y)) map->getTilePointer(x, y)->background = TCOD_pink;
		}
	}
}