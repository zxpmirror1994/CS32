#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED
#include "Board.h"

class Player
{
public:
    Player(std::string name);
    
    std::string name() const;
   
    virtual bool isInteractive() const;
    
    virtual int chooseMove(const Board& b, Side s) const = 0;
   
    virtual ~Player();
private:
    std::string m_name;

};

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string name);
    
    virtual bool isInteractive() const;
    
    virtual int chooseMove(const Board& b, Side s) const;
    
    virtual ~HumanPlayer();
    
};

class BadPlayer : public Player
{
public:
    BadPlayer(std::string name);
    
    virtual int chooseMove(const Board& b, Side s) const;
    
    virtual ~BadPlayer();
};

class SmartPlayer : public Player
{
public:
    SmartPlayer(std::string name);
    
    virtual int chooseMove(const Board& b, Side s) const;
    
    virtual ~SmartPlayer();
private:
    struct Node
    {
        Board n_board;
        Node* child[20];
    };
    
    int evaluate(Node* bn, Side s) const;
};



#endif  //PLAYER_INCLUDED
