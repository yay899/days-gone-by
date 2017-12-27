//
// Created by clayton on 12/25/17.
//

#include "BspListener.hpp"
#include <iostream>


BspListener::BspListener(Floor *floor1){
    floor = floor1;
    roomNum = 0;
}

bool BspListener::BspListener::visitNode(TCODBsp *node, void *userData){
    if (node->isLeaf()) {
        int x, y, w, h;
        // dig a room
        TCODRandom *rng = TCODRandom::getInstance();

        if (rng->getInt(0,20)>2){
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

            floor->setRectangle(y - h / 2 - 1, x - w / 2 - 1, (w), (h),
                                TileNormal('#', TCOD_white, TCOD_black, true, false, false),
                                TileNormal('.', TCOD_white, TCOD_black, true, false, true));


            /*if ( roomNum != 0 ) {
                // dig a corridor from last room

            }
            lastx=x;
            lasty=y;
            roomNum++;*/
        }
    }
    return true;

}