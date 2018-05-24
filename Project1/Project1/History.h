#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED
#include "globals.h"
#include <iostream>


class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_h_row;
    int m_h_col;
    int m_history[MAXROWS][MAXCOLS];
    
};

#endif   // HISTORY_INCLUDED