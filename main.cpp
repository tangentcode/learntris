#include "Tetro.h"
#include <iostream>

int main (int argc, char *argv[])
{
    Tetro tetro(1);
    Board board;
    tetro.current_location_x = 5;
    tetro.current_location_y = 20;

    tetro.moveTetro('d',board);
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            std::cout << tetro.current_tetro[i][j];
        }
        std::cout << std::endl;
    }
    board.printBoard();


    return 0;
}
/*
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            std::cout << tetro.current_tetro[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "done";
    tetro.rotateTetro(board);
    board.printBoard();



*/
