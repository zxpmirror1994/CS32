#ifndef GAME_INCLUDED
#define GAME_INCLUDED
#include "Board.h"
#include "Player.h"

class Game
{
public:
    Game(const Board& b, Player* south, Player* north);
    
    void display() const;
    
    void status(bool& over, bool& hasWinner, Side& winner) const;
   
    bool move();
                                                                                                        
    void play();
    
    int beans(Side s, int hole) const;
private:
    Board m_board;
    
    Player* m_player1;
    
    Player* m_player2;
    
    bool m_over;
    
    Side m_turn;
    
};

#endif  //GAME_INCLUDED