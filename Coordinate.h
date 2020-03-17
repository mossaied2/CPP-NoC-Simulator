#pragma once
#ifndef __COORD_H__
#define __COORD_H__

#include "Constants.h"

struct Position {
    int x;			// X coordinate
    int y;			// Y coordinate
    int z;			// Y coordinate

    inline bool operator ==(const Position& position) const {
        return (position.x == x && position.y == y && position.z == z);
    }
};
  
class Coord {
    
public:
    int x;			// X coordinate
    int y;			// Y coordinate
    int z;			// Y coordinate
    Position postion;

    Position id2Coord(int const local_id) {
        Position position;
        int x, y, z;

        z = local_id / (DIMX * DIMY);////
        y = (local_id - z * DIMX * DIMY) / DIMX;
        x = (local_id - z * DIMX * DIMY) % DIMX;

        position.x = x;
        position.y = y;
        position.z = z;


        assert(x < DIMX);
        assert(y < DIMY);
        assert(z < DIMZ);

        return position;
    }

    int Coord2id(int const x, int const y, int const z) {
        return x + y * DIMX + z * DIMX * DIMY;
    }
};

#endif