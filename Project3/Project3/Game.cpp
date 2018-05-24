#include "Game.h"

//Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
Game::Game(const Board& b, Player* south, Player* north)
:m_board(b), m_player1(south), m_player2(north), m_over(false), m_turn(SOUTH)
{
}

//The display pattern is like
//      NORTH_NAME
//   N_HOLE#1   N_HOLE#2  .....
//NORTH_POT               SOUTH_POT
//   S_HOLE#1   S_HOLE#2  .....
//      SOUTH_NAME
void Game::display() const
{
    std::cout << "   " <<  m_player2->name() << std::endl;
    std::cout << "   ";
    for (int j = 1; j <= m_board.holes(); j++)
    {
        std::cout << m_board.beans(NORTH, j) << " ";
    }
    std::cout << std::endl;
    
    std::cout << m_board.beans(NORTH, 0) << "         " << m_board.beans(SOUTH, 0) << std::endl;
    
    std::cout << "   ";
    for (int j = 1; j <= m_board.holes(); j++)
    {
        std::cout << m_board.beans(SOUTH, j) << " ";
    }
    std::cout << std::endl;
    std::cout << "   " <<  m_player1->name() << std::endl;
}

//If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    if (m_board.beansInPlay(SOUTH) != 0 && m_board.beansInPlay(NORTH) != 0)
    {
        over = false;
    }
    else
    {
        over = true;
        if ((m_board.beansInPlay(SOUTH) + m_board.beans(SOUTH, 0)) > (m_board.beansInPlay(NORTH) + m_board.beans(NORTH, 0)))
        {
            hasWinner = true;
            winner = SOUTH;
        }
        else if ((m_board.beansInPlay(SOUTH) + m_board.beans(SOUTH, 0)) < (m_board.beansInPlay(NORTH) + m_board.beans(NORTH, 0)))
        {
            hasWinner = true;
            winner = NORTH;
        }
        else
        {
            hasWinner = false;
        }
    }
}

//If the game is over, return false. Otherwise, make a complete move for the player whose turn it is (so that it becomes the other player's turn) and return true. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. If the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.
bool Game::move()
{
    if (m_over == true)
    {
        return false;
    }
    else
    {
        if (m_turn == SOUTH)
        {
            int move = m_player1->chooseMove(m_board, SOUTH);
            Side endSide;
            int endHole;
            if (m_board.sow(SOUTH, move, endSide, endHole))
            {
                //After sowing, if no beans are in south holes, put all beans in north holes into north pot and make the game over
                if (m_board.beansInPlay(SOUTH) == 0)
                {
                    m_over = true;
                    for (int i = 1; i <= m_board.holes(); i++)
                    {
                        m_board.moveToPot(NORTH, i, NORTH);
                    }
                    return true;
                }
                //If the last bean is placed in north hole, it will be north turn
                if (endSide == NORTH)
                {
                    m_turn = NORTH;
                    return true;
                }
                //capture
                else if (endSide == SOUTH && m_board.beans(SOUTH, endHole) == 1 && m_board.beans(NORTH, endHole) != 0)
                {
                    if (m_board.moveToPot(SOUTH, endHole, SOUTH) && m_board.moveToPot(NORTH, endHole, SOUTH))
                    {
                        m_turn = NORTH;
                        return true;
                    }
                }
                //additional turns happen until the last bean is not put into south pot
                while (endSide == SOUTH && endHole == 0)
                {
                    display();
                    if (m_board.sow(SOUTH, m_player1->chooseMove(m_board, SOUTH), endSide, endHole))
                    {
                        display();
                    }
                }
                if (m_board.beansInPlay(SOUTH) == 0)
                {
                    m_over = true;
                    for (int i = 1; i <= m_board.holes(); i++)
                    {
                        m_board.moveToPot(NORTH, i, NORTH);
                    }
                    return true;
                }
                //If the last bean is placed in north hole, it will be north turn
                if (endSide == NORTH)
                {
                    m_turn = NORTH;
                    return true;
                }
                //capture
                else if (endSide == SOUTH && m_board.beans(SOUTH, endHole) == 1 && m_board.beans(NORTH, endHole) != 0)
                {
                    if (m_board.moveToPot(SOUTH, endHole, SOUTH) && m_board.moveToPot(NORTH, endHole, SOUTH))
                    {
                        m_turn = NORTH;
                        return true;
                    }
                }
                m_turn = NORTH;
                return true;
            }
            else
            {
                m_over = true;
                return false;
            }
        }
        if (m_turn == NORTH)
        {
            int move = m_player2->chooseMove(m_board, NORTH);
            Side endSide;
            int endHole;
            if (m_board.sow(NORTH, move, endSide, endHole))
            {
                //After sowing, if no beans are in north holes, put all beans in south holes into south pot and make the game over
                if (m_board.beansInPlay(NORTH) == 0)
                {
                    m_over = true;
                    for (int i = 1; i <= m_board.holes(); i++)
                    {
                        m_board.moveToPot(SOUTH, i, SOUTH);
                    }
                    return true;
                }
                //If the last bean is placed in south hole, it will be south turn
                if (endSide == SOUTH)
                {
                    m_turn = SOUTH;
                    return true;
                }
                //capture
                else if (endSide == NORTH && m_board.beans(NORTH, endHole) == 1 && m_board.beans(SOUTH, endHole) != 0)
                {
                    if (m_board.moveToPot(NORTH, endHole, NORTH) && m_board.moveToPot(SOUTH, endHole, NORTH))
                    {
                        m_turn = SOUTH;
                        return true;
                    }
                }
                //additional turns happen until the last bean is not put into north pot
                while (endSide == NORTH && endHole == 0)
                {
                    display();
                    if (m_board.sow(NORTH, m_player2->chooseMove(m_board, NORTH), endSide, endHole))
                    {
                        display();
                    }
                }
                if (m_board.beansInPlay(NORTH) == 0)
                {
                    m_over = true;
                    for (int i = 1; i <= m_board.holes(); i++)
                    {
                        m_board.moveToPot(SOUTH, i, SOUTH);
                    }
                    return true;
                }
                //If the last bean is placed in south hole, it will be south turn
                if (endSide == SOUTH)
                {
                    m_turn = SOUTH;
                    return true;
                }
                //capture
                else if (endSide == NORTH && m_board.beans(NORTH, endHole) == 1 && m_board.beans(SOUTH, endHole) != 0)
                {
                    if (m_board.moveToPot(NORTH, endHole, NORTH) && m_board.moveToPot(SOUTH, endHole, NORTH))
                    {
                        m_turn = SOUTH;
                        return true;
                    }
                }
                m_turn = SOUTH;
                return true;
            }
            else
            {
                m_over = true;
                return false;
            }
        }
    }
    return true;
}

//Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function.
void Game::play()
{
    display();
    while (!m_over && move())
    {
        display();
        if (!m_player1->isInteractive() && !m_player2->isInteractive())
        {
            std::cout << "Press ENTER to continue";
            std::cin.ignore(10000, '\n');
        }
    }
    bool hasWinner = true;
    status(m_over, hasWinner, m_turn);
    if (hasWinner == false)
    {
        std::cout << "The game is tied" << std::endl;
    }
    else if(m_turn == SOUTH)
    {
        std::cout << "The winner is " << m_player1->name() << std::endl;
    }
    else if (m_turn == NORTH)
    {
        std::cout << "The winner is " << m_player2->name() << std::endl;
    }
}

int Game::beans(Side s, int hole) const
{
    if (hole < 0 || hole > m_board.holes())
    {
        return -1;
    }
    else
    {
        return m_board.beans(s, hole);
    }
}
