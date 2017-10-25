#pragma once
#ifndef UPDATE_HPP
#define UPDATE_HPP

#include "libtcod.hpp"
#include "Map.hpp"
#include "Menu.hpp"

enum State {
	STATE_PLAYER_TURN,
	STATE_AI_TURN,
	STATE_IN_MENU
};

void update(Map* map);

#endif