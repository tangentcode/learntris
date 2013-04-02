#ifndef _Board_
#define _Board_

#include <cstring>
#include <iostream>
class Board
{
public:
    Board();

    enum {BLOC_NULL, BLOC_FILL, BLOC_SIDE};
    int boardState[25][12];
    bool getSpace(int x);
    void initBoard();
    void printBoard();
    friend class Tetro;
};

Board::Board()
{
    memset(boardState, BLOC_NULL, sizeof(boardState));
}
/*--------------------------
Sets up walls on the board
----------------------------*/
void Board::initBoard()
{
    memset(boardState, BLOC_NULL, sizeof(boardState));
    for (int i = 0; i < 25; i++)
    {
        boardState[i][0] = 2;
        boardState[i][11] = 2;
    }
    for(int i = 0; i < 12; i++)
    {
        boardState[24][i] = 2;
    }
}
/*--------------------------
Early cout boardview for diag
----------------------------*/

void Board::printBoard()
{
    for (int k=0; k< 300; k++)
    {
        std::cout << *((*boardState) + k);
        if ((k+1)%12 == 0)
        {
            std::cout << std::endl;
        }
    }
    for (int k=0; k< 300; k++)
    {
        if(getSpace(k))
        {
            std::cout << 0;
        }
        else
        {
            std::cout << 1;
        }
    }
}
/*--------------------------
Who knows
----------------------------*/
bool Board::getSpace(int x)
{
    if (*((*boardState) + x) != BLOC_NULL)
    {
        return true;
    }
    else
    {
        return false;
    }

}
#endif
