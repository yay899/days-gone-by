//
// Created by clayton on 12/25/17.
//

#include "FloorGenListener.hpp"
#include "libtcod.hpp"
#include <iostream>

FloorGenListener::FloorGenListener(Floor *floor1){//have this accept two templates
    floor = floor1;
    roomNum = 0;
    edgeOfRoom = false;
}
/*
template <class TileType>
void FloorGenListener::floorSet(TileType out, TileType fil){
    outline = static_cast<int>(&out);
    fill = static_cast<int>(&fil);
}*/

bool FloorGenListener::visitNode(TCODBsp *node, void *userData){
    if (node->isLeaf()) {
        int x, y, w, h;
        // dig a room
        TCODRandom *rng = TCODRandom::getInstance();

        if (rng->getInt(0,20)>-1){//if not currently in use
            std::cout << node->w - 2 << std::endl;
            w = rng->getInt(10, node->w - 2);
            std::cout << node->h - 2 << std::endl;
            h = rng->getInt(7, node->h - 2);

            x = node->x + (node->w) / 2;
            //std::cout<<node->x+1<<std::endl;
            //std::cout<<node->w-w-1<<std::endl;

            y = node->y + (node->h) / 2;
            //std::cout<<node->y+1<<std::endl;
            //std::cout<<node->h-h-1<<std::endl;

            std::cout << y - (h - 2) / 2 << std::endl;
            std::cout << x - (w - 2) / 2 << std::endl;

            floor->setRectangle(y - h / 2 - 1, x - w / 2 - 1, (w), (h), TileNormal('.', TCOD_dark_grey, TCOD_black, true, false, false), TileNormal(' ', TCOD_dark_grey, TCOD_black, true, false, true));


            if ( roomNum != 0 ) {
                // dig a corridor from last room

                lastPointX = -1;
                lastPointY = -1;
                TCODLine::line(lastRoomX,lastRoomY,x,y,&(*this));
            }
            lastRoomX=x;
            lastRoomY=y;
            roomNum++;
        }
    }
    return true;

	}
	bool FloorGenListener::putPoint (int x,int y) {
        //if(!floor->getTile(y,x).isWalkable()){

            floor->setTile(x+1,y, TileNormal(' ', TCOD_dark_grey, TCOD_black, true, false, true));
            floor->setTile(x-1,y, TileNormal(' ', TCOD_dark_grey, TCOD_black, true, false, true));
            floor->setTile(x,y+1, TileNormal(' ', TCOD_dark_grey, TCOD_black, true, false, true));
            floor->setTile(x,y-1, TileNormal(' ', TCOD_dark_grey, TCOD_black, true, false, true));
            floor->setTile(x,y, TileNormal(' ', TCOD_dark_grey, TCOD_black, true, false, true));

       return true;
	}

/*template void FloorGenListener::floorSet<TileNormal>(TileNormal, TileNormal);
template void FloorGenListener::floorSet<TileDoor>(TileDoor, TileDoor);

template void FloorGenListener::outline<TileNormal>;
template void FloorGenListener::outline<TileDoor>;*/

