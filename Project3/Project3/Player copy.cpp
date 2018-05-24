#include "Player.h"

//Create a Player with the indicated name.
Player::Player(std::string name)
:m_name(name)
{}

//name() is a non-virtual function, so we only need to implement it once.
std::string Player::name() const
{
    return m_name;
}

//Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
bool Player::isInteractive() const
{
    return false;
}

Player::~Player()
{}

HumanPlayer::HumanPlayer(std::string name)
:Player(name)
{}

//For human player, isInteractive() returns true
bool HumanPlayer::isInteractive() const
{
    return true;
}

int HumanPlayer::chooseMove(const Board &b, Side s) const
{
    if (b.beansInPlay(s) == 0)
    {
        return -1;
    }
start:
    std::cout << "Select a hole, " << name() << " :";
    int hole;
    std::cin >> hole;
    if (hole > 0 && hole <= b.holes() && b.beans(s, hole) > 0)
    {
        return hole;
    }
    //special case for invalid picking of a player
    else if (b.beans(s, hole) == 0)
    {
        std::cout << "There are no beans in that hole." << std::endl;
        goto start;
    }
    else
    {
        std::cout << "The hole number must be from 1 to " << b.holes() << std::endl;
        goto start;
    }
}

HumanPlayer::~HumanPlayer()
{}

BadPlayer::BadPlayer(std::string name)
:Player(name)
{}

//Return the index of the first valid hole
int BadPlayer::chooseMove(const Board &b, Side s) const
{
    if (b.beansInPlay(s) == 0)
    {
        return -1;
    }
    
    for (int i = 1; i <= b.holes(); i++)
    {
        if (b.beans(s, i) > 0)
        {
            std::cout << name() << " chooses hole " << i << std::endl;
            return i;
        }
    }
    return -1;
}

BadPlayer::~BadPlayer()
{}

SmartPlayer::SmartPlayer(std::string name)
:Player(name)
{}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    int value = 0;
    int bestHole = 1;
    int depth = 1;
    Node* root;
    root->data = b;
    
    chooseMove1(root,s, bestHole,value, depth);
    return bestHole;
    // for every hole h the player can choose
    //  "make" the move h
    //    chooseMove(opponent, h2, v2)
    //   "unmake" the move
    //   if v2 is better for the player than best seen so far,
    //      bestHole = h
    //      value = v2
}


SmartPlayer::~SmartPlayer()
{}

SmartPlayer::int SmartPlayer::evaluate(int hole, int depth)
{
    
}
