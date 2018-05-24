#include "History.h"
#include <iostream>
using namespace std;


History::History(int nRows, int nCols)
{
    m_h_row = nRows;
    m_h_col = nCols;
    for (int r = 0; r < nRows; r++)
    {
        for (int c = 0; c < nCols; c++)
        {
            m_history[r][c] = 0;
        }
    }
}

bool History::record(int r, int c)
{
    if (r < 1 || r > m_h_row || c < 1 || c > m_h_col)
    {
        return false;
    }
    else
    {
        m_history[r - 1][c - 1]++;
        return true;
    }
}

void History::display() const
{
    char displayGrid[m_h_row][m_h_col];
    
    for (int r = 1; r <= m_h_row; r++)
    {
        for (int c = 1; c <= m_h_col; c++)
        {
            if (m_history[r - 1][c - 1] == 0)
            {
                displayGrid[r - 1][c - 1] = '.';
            }
            else if (m_history[r - 1][c - 1] >= 26)
            {
                displayGrid[r - 1][c - 1] = 'Z';
            }
            else
            {
                displayGrid[r - 1][c - 1] = m_history[r - 1][c - 1] + 64;
            }
        }
    }
    
    clearScreen();
    for (int r_new = 1; r_new <= m_h_row; r_new++)
    {
        for (int c_new = 1; c_new <= m_h_col; c_new++)
            cout << displayGrid[r_new - 1][c_new - 1];
        cout << endl;
    }
    cout << endl;
}