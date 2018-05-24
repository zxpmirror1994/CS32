#include <iostream>
#include <cstring>
using namespace std;


bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
    {
        return true;
    }
    maze[sr][sc] = 'E';
    //North
    if (maze[sr - 1][sc] == '.')
    {
        if (pathExists(maze, sr - 1, sc, er, ec))
        {
            return true;
        }
    }
    //East
    if (maze[sr][sc + 1] == '.')
    {
        if (pathExists(maze, sr, sc + 1, er, ec))
        {
            return true;
        }
    }
    //South
    if (maze[sr + 1][sc] == '.')
    {
        if (pathExists(maze, sr + 1, sc, er, ec))
        {
            return true;
        }
    }
    //West
    if (maze[sr][sc - 1] == '.')
    {
        if (pathExists(maze, sr, sc - 1, er, ec))
        {
            return true;
        }
    }
    return false;
}
