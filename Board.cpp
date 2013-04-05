#include "Board.h"
#include <iostream>

Board::Board()
{
    memset(boardState, BLOC_NULL, sizeof(boardState));
    for (int i = 0; i < 23; i++)
    {
        boardState[i][0] = 2;
        boardState[i][11] = 2;
    }
    for(int i = 0; i < 12; i++)
    {
        boardState[22][i] = 2;
    }
};
Board::~Board()
{

};

/*--------------------------
Early cout boardview for diag
----------------------------*/

void Board::printBoard()
{
    for (int k=0; k< 276; k++)
    {
        std::cout << *((*boardState) + k);
        if ((k+1)%12 == 0)
        {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
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

void Board::writeToBoard(int locX, int locY, int shape_to_write[][2])
{
    int wX, wY;
    for(int i = 0; i < 4; i++)
    {
        wX = shape_to_write[i][0] + locX;
        wY = shape_to_write[i][1] + locY;
        std::cout << wX << " " << wY << std::endl;
        boardState[wY][wX] = 1;

    }
}
