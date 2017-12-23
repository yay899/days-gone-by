//
// Created by clayton on 12/23/17.
//

#ifndef DAYS_GONE_BY_DUNGEON_H
#define DAYS_GONE_BY_DUNGEON_H

class Dungeon{
private:

    Floor** Floors;
public:
    Floor* currFloor;

    /**
      sets the current floor to the given floor
      0-x

      @param the floor to go to
     */
    void setCurrentFloor(unsigned int i);

    unsigned int addFloor(Floor* floor);

    /**
        Adds a floor and sets it to the current floor.

        @param floor to be added
        @returns index
    */
    unsigned int addCurrentFloor(Floor* floor);

    /*
        Gets floor at index.

        @param index of floor
        @returns pointer to floor
    */
    Floor* getFloor(unsigned int i);

    /*
        Gives index of floor pointer. (-1 is failure to find.)

        @param pointer of floor
        @returns index
    */
    int findFloor(Floor* floor);

    /*
        Removes floor at index.

        @param index of floor.
    */
    void removeFloor(unsigned int i);


};

#endif //DAYS_GONE_BY_DUNGEON_H
