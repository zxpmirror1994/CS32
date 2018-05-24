#include <iostream>
#include <queue>
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
    queue<Coord> coordQueue;
    coordQueue.push(Coord(sr, sc));
    maze[sr][sc] = 'E';
    while (!coordQueue.empty())
    {
        int r = coordQueue.front().r();
        int c = coordQueue.front().c();
        coordQueue.pop();
        if (r == er && c == ec)
        {
            return true;
        }
        //North
        if (maze[r - 1][c] == '.')
        {
            coordQueue.push(Coord(r - 1, c));
            maze[r - 1][c] = 'E';
        }
        //East
        if (maze[r][c + 1] == '.')
        {
            coordQueue.push(Coord(r, c + 1));
            maze[r][c + 1] = 'E';
        }
        //South
        if (maze[r + 1][c] == '.')
        {
            coordQueue.push(Coord(r + 1, c));
            maze[r + 1][c] = 'E';
        }
        //West
        if (maze[r][c - 1] == '.')
        {
            coordQueue.push(Coord(r, c - 1));
            maze[r][c - 1] = 'E';
        }
    }
    return false;
}
