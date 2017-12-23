//
// Created by clayton on 12/23/17.
//

#include "Dungeon.hpp"

unsigned int Dungeon::addFloor(Floor* floor) {
    Floors.push_back(floor);
    return (unsigned int)Floors.size() - 1;
}

unsigned int Dungeon::addCurrentFloor(Floor* floor) {
    currentFloor = floor;
    Floors.push_back(floor);
    return (unsigned int)Floors.size() - 1;
}

Floor* Dungeon::getFloor(unsigned int i) {
    return Floors.at(i);
}

int Dungeon::findFloor(Floor* floor) {
    for (unsigned int i = 0; i < Floors.size() - 1; i++) {
        if (Floors.at(i) == floor) return i;
    }

    return -1;
}

void Dungeon::removeFloor(unsigned int i) {
    delete Floors.at(i);
    Floors.erase(Floors.begin() + i);
}R