//
// Created by clayton on 12/25/17.
//

#ifndef DAYS_GONE_BY_BSPLISTENER_HPP
#define DAYS_GONE_BY_BSPLISTENER_HPP

#include "libtcod.hpp"
#include "Floor.hpp"
#include "TileNormal.hpp"
#include "TileDoor.hpp"

class FloorGenListener: public ITCODBspCallback, public TCODLineListener{

private :
    Floor *floor; // a map to dig
    int roomNum; // room number
    int lastPointX, lastPointY; // center of the last room
	bool edgeOfRoom;


public :
	int lastRoomX,lastRoomY;
	FloorGenListener(Floor* floor1);

	/*template <class TileType>
	void floorSet(TileType, TileType);*/

    bool visitNode(TCODBsp *node, void *userData);
	bool putPoint (int x,int y);
};


#endif //DAYS_GONE_BY_BSPLISTENER_HPP
