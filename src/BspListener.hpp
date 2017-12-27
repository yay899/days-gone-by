//
// Created by clayton on 12/25/17.
//

#include "libtcod.hpp"
#include "Floor.hpp"

#ifndef DAYS_GONE_BY_BSPLISTENER_HPP
#define DAYS_GONE_BY_BSPLISTENER_HPP

class BspListener: public ITCODBspCallback{
private :
    Floor *floor; // a map to dig
    int roomNum; // room number
    int lastx,lasty; // center of the last room
public :
    BspListener(Floor *floor);
    bool visitNode(TCODBsp *node, void *userData);
};


#endif //DAYS_GONE_BY_BSPLISTENER_HPP
