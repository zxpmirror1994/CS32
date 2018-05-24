#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};


bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;
    coordStack.push(Coord(sr, sc));  //push the start coord onto the stack
    maze[sr][sc] = 'E';   //Since we have visited the starting coord, assign it to 'E'
    while (!coordStack.empty())
    {
        int r = coordStack.top().r();
        int c = coordStack.top().c();
        coordStack.pop();
        if (r == er && c == ec)
        {
            return true;
        }
        //North
        if (maze[r - 1][c] == '.')
        {
            coordStack.push(Coord(r - 1, c));
            maze[r - 1][c] = 'E';
        }
        //East
        if (maze[r][c + 1] == '.')
        {
            coordStack.push(Coord(r, c + 1));
            maze[r][c + 1] = 'E';
        }
        //South
        if (maze[r + 1][c] == '.')
        {
            coordStack.push(Coord(r + 1, c));
            maze[r + 1][c] = 'E';
        }
        //West
        if (maze[r][c - 1] == '.')
        {
            coordStack.push(Coord(r, c - 1));
            maze[r][c - 1] = 'E';
        }
    }
    return false;
}
