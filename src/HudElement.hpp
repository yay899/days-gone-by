#pragma once
#ifndef HUDELEMENT_HPP
#define HUDELEMNET_HPP

#include <string>

#include "Entity.hpp"
#include"libtcod.hpp"

class HudElement {
public:
	std::string display;
	TCODColor col;

	/**
		@param text color
		@param display string
	*/
	HudElement(TCODColor = TCODConsole::root->getDefaultForeground(), std::string = "");

	/**
		Extend this with complex functionality.
	*/
	virtual void update();
};

class HudElementHp : public HudElement {
public:
	Entity* e;

	/**
		@param tracked Entity.
	*/
	HudElementHp(Entity*);

	/**
		Fetches HP of entity
	*/
	void update();
};

class HudElementWatts : public HudElement {
public:
	Entity* e;

	/**
		@param tracked Entity.
	*/
	HudElementWatts(Entity*);

	/**
		Fetches HP of entity
	*/
	void update();
};

#endif