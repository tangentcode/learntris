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
        boardState[wY][wX] = 1;

    }
}

void Board::checkBoard(Board board)
{
    int filled_blocks = 0;
    for(int i = 0; i < 22; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            if(boardState[i][j] > 0)
            {
                filled_blocks++;
                std::cout << filled_blocks << std::endl;
                //***Loop that sets each block to that of the block above it***
                if(filled_blocks == 12)
                {

                    for(int ii = i; ii != 0; ii--)
                    {
                        int row_above = ii;
                        row_above--;
                        for(int j = 0; j < 12; j++)
                        {
                            boardState[ii][j] = boardState[row_above][j];
                        }
                    }
                }
            }
        }
        filled_blocks = 0;
    }
}






