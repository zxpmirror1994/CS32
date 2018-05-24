#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED
#include "Side.h"

class Board
{
public:
    Board(int nHoles, int nInitialBeansPerHole);
   
    int holes() const;
    
    int beans(Side s, int hole) const;
    
    int beansInPlay(Side s) const;
    
    int totalBeans() const;
    
    bool sow(Side s, int hole, Side& endSide, int& endHole);
    
    bool moveToPot(Side s, int hole, Side potOwner);
    
    bool setBeans(Side s, int hole, int beans);
private:
    struct Hole
    {
        int holeIndex;
        
        Side holeSide;
        
        int numOfBeans;
        
        Hole* m_next;
    };
    
    int m_size;
    
    Hole* nhp;
    
    Hole* npp;
    
    Hole* shp;
    
    Hole* spp;
};

#endif  //BOARD_INCLUDED