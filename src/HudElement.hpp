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

	HudElement(TCODColor col = TCODConsole::root->getDefaultForeground(), std::string d = "");

	/*
		Extend this with complex functionality.
	*/
	virtual void update();
};

class HudElementHp : public HudElement {
public:
	Entity* e;

	HudElementHp(Entity* e);

	/*
		Fetches HP of entity
	*/
	void update();
};

class HudElementWatts : public HudElement {
public:
	Entity* e;

	HudElementWatts(Entity* e);

	/*
	Fetches HP of entity
	*/
	void update();
};

#endif