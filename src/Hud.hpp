#pragma once
#ifndef HUD_HPP
#define HUD_HPP

#include <vector>

#include "libtcod.hpp"
#include "HudElement.hpp"

extern const unsigned int SCREEN_WIDTH;
extern const unsigned int SCREEN_HEIGHT;

class Hud {
protected:
	std::vector<HudElement*> elements;
	unsigned int w;

public:

	/**
		@param width
	*/
	Hud(unsigned int);
	~Hud();

	/**
		Updates all elements in hud.
	*/
	void update();

	/**
		Renders hud.
	*/
	void render();

	/**
		Adds a element to the hud

		@param element to add
	*/
	void addElement(HudElement*);
};

//Constants
const TCODColor HUD_BACKGROUND = TCOD_black;
#endif