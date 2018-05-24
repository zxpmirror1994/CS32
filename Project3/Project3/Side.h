#ifndef SIDE_INCLUDED
#define SIDE_INCLUDED
#include <iostream>

enum Side { NORTH, SOUTH };

inline
Side opponent(Side s)
{
    return Side(1 - s);
}

#endif   //SIDE_INCLUDED