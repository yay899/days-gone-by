#include "Hud.hpp"

Hud::Hud(unsigned int w) : elements(std::vector<HudElement*>()), w(w) {

}

Hud::~Hud() {
	for (std::vector<HudElement*>::iterator i = elements.begin(); i < elements.end(); i++)
		delete *i;
}

void Hud::update() {
	for (std::vector<HudElement*>::iterator i = elements.begin(); i < elements.end(); i++)
		(*i)->update();
}

void Hud::render() {
	
	//Store old default colors and set new ones.
	TCODColor oldBackground = TCODConsole::root->getDefaultBackground();
	TCODColor oldForeground = TCODConsole::root->getDefaultForeground();
	TCOD_bkgnd_flag_t oldFlag = TCODConsole::root->getBackgroundFlag();
	TCOD_alignment_t oldAlignment = TCODConsole::root->getAlignment();
	TCODConsole::root->setDefaultBackground(HUD_BACKGROUND);
	TCODConsole::root->setBackgroundFlag(TCOD_BKGND_SET);
	TCODConsole::root->setAlignment(TCOD_LEFT);

	//Clear rectangle
	for (unsigned int x = SCREEN_WIDTH - w; x < SCREEN_WIDTH; x++) {
		for (unsigned int y = 0; y < SCREEN_HEIGHT; y++) {
			TCODConsole::root->setChar(x, y, ' ');
			TCODConsole::root->setCharBackground(x, y, HUD_BACKGROUND);
		}
	}

	//Print elements
	for (unsigned int y = 0; y < elements.size(); y++) {
		TCODConsole::root->setDefaultForeground(elements.at(y)->col);
		TCODConsole::root->print(SCREEN_WIDTH - w, y, elements.at(y)->display.c_str());
	}

	//Restore default colors.
	TCODConsole::root->setDefaultBackground(oldBackground);
	TCODConsole::root->setDefaultForeground(oldForeground);
	TCODConsole::root->setBackgroundFlag(oldFlag);
	TCODConsole::root->setAlignment(oldAlignment);
}

void Hud::addElement(HudElement* e) {
	elements.push_back(e);
}