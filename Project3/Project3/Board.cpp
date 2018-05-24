#include "Board.h"

//Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole.

//I use a circular single linked list to construct the Board class
//Since Kalah operates in counterclockwise direction, what I need to care about is just the reverse indeces for the north holes array
//In north or south holes array, the m_next pointer points to next element
//m_next of the first element of the north holes array points to the north pot, and m_next of the last element of the south holes array points to the south pot
//Initialize the side and the index respectively
Board::Board(int nHoles, int nInitialBeansPerHole)
:m_size(2 * nHoles + 2)
{
    if (nInitialBeansPerHole < 0 || nHoles <= 0)
    {
        exit(1);
    }
    nhp = new Hole[nHoles + 1];
    shp = new Hole[nHoles + 1];
    npp = nhp + nHoles;
    spp = shp + nHoles;
    
    npp->m_next = shp;
    spp->m_next = nhp;
    
    
    int numOfHolesPerSide = nHoles;
    
    for (Hole* p = nhp; p != npp && numOfHolesPerSide > 0; p++)
    {
        p->holeSide = NORTH;
        p->numOfBeans = nInitialBeansPerHole;
        p->m_next = p + 1;
        p->holeIndex = numOfHolesPerSide;
        numOfHolesPerSide--;
    }
    
    for (Hole* q = shp; q != spp && numOfHolesPerSide <= nHoles; q++)
    {
        q->holeSide = SOUTH;
        q->numOfBeans = nInitialBeansPerHole;
        q->m_next = q + 1;
        q->holeIndex = numOfHolesPerSide + 1;
        numOfHolesPerSide++;
    }
    
    npp->holeIndex = 0;
    spp->holeIndex = 0;
    
    npp->numOfBeans = 0;
    spp->numOfBeans = 0;
    
    npp->holeSide = NORTH;
    spp->holeSide = SOUTH;
    
}

//Return the number of holes on a side (not counting the pot).
int Board::holes() const
{
    return (m_size - 2) / 2;
}

//Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
int Board::beans(Side s, int hole) const
{
    if (hole > holes() || hole < 0)
    {
        return -1;
    }
    else
    {
        //Find the pointer that terminates our searching
        Hole* p = nhp;
        for (; p->holeIndex != hole || p->holeSide != s; p = p->m_next)
        {
            ;
        }
        return p->numOfBeans;
    }
}

//Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
int Board::beansInPlay(Side s) const
{
    int numOfBeansOnIndicatedSide = 0;
    if (s == SOUTH)
    {
        for (Hole* p = shp; p != spp; p = p->m_next)
        {
            numOfBeansOnIndicatedSide += p->numOfBeans;
        }
    }
    else if (s == NORTH)
    {
        for (Hole* q = nhp; q != npp; q = q->m_next)
        {
            numOfBeansOnIndicatedSide += q->numOfBeans;
        }
    }
    return numOfBeansOnIndicatedSide;
}

//Return the total number of beans in the game.
int Board::totalBeans() const
{
    return beansInPlay(NORTH) + beansInPlay(SOUTH) + npp->numOfBeans + spp->numOfBeans;
}


//If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    if (beans(s, hole) == 0 || hole > holes() || hole <= 0)
    {
        return false;
    }
    else
    {
        Hole* p = nhp;
        for (; p->holeIndex != hole || p->holeSide != s; p = p->m_next)
        {
            ;
        }
        //We need a variable to copy the value of the beans in this hole
        int numOfBeans = p->numOfBeans;
        p->numOfBeans = 0;
        while (numOfBeans != 0)
        {
            if ((s == SOUTH && p->m_next == npp) || (s == NORTH && p->m_next == spp))
            {
                p = p->m_next;
                continue;
            }
            p->m_next->numOfBeans++;
            p = p->m_next;
            numOfBeans--;
        }
        endSide = p->holeSide;
        endHole = p->holeIndex;
        return true;
    }
}

//If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    if (hole <= holes() && hole > 0)
    {
        Hole* p = nhp;
        for (; p->holeIndex != hole || p->holeSide != s; p = p->m_next)
        {
            ;
        }
        if (potOwner == SOUTH)
        {
            spp->numOfBeans += p->numOfBeans;
        }
        else if (potOwner == NORTH)
        {
            npp->numOfBeans += p->numOfBeans;
        }
        p->numOfBeans = 0;
        return true;
    }
    return false;
}

//If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This may change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)
bool Board::setBeans(Side s, int hole, int beans)
{
    if (hole > holes() || hole < 0 || beans < 0)
    {
        return false;
    }
    else
    {
        Hole* p =nhp;
        for (; p->holeIndex != hole || p->holeSide != s; p = p->m_next)
        {
            ;
        }
        p->numOfBeans = beans;
        return true;
    }
}