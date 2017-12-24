//
// Created by clayton on 12/23/17.
//

#ifndef DAYS_GONE_BY_DUNGEON_H
#define DAYS_GONE_BY_DUNGEON_H
#include "Floor.hpp"
#include <vector>

class Dungeon{
private:

    std::vector<Floor*> Floors;
public:
    Floor* currentFloor;

    /**
		Sets current floor to target floor.
		0-x

		@param index of target floor
     */
    void setCurrentFloor(unsigned int);

	/**
		Adds a floor.

		@return index of floor
	*/
    unsigned int addFloor(Floor*);

    /**
        Adds a floor and sets it to the current floor.

        @param floor to be added
        @return index
    */
    unsigned int addCurrentFloor(Floor*);

    /**
        Gets floor at index.

        @param index of floor
        @return pointer to floor
    */
    Floor* getFloor(unsigned int);

    /**
        Gives index of floor pointer. (-1 is failure to find.)

        @param pointer of floor
        @return index
    */
    int findFloor(Floor*);

    /**
        Removes floor at index.

        @param index of floor.
    */
    void removeFloor(unsigned int);


};

#endif //DAYS_GONE_BY_DUNGEON_H
