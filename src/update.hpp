#pragma once
#ifndef UPDATE_HPP
#define UPDATE_HPP

#include "libtcod.hpp"
#include "Map.hpp"

enum State {
	STATE_PLAYER_TURN,
	STATE_AI_TURN
};

void update(Map* map);

#endif