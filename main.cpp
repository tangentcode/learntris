#include "Tetro.h"
#include <iostream>
#include <ios>

int main (int argc, char *argv[])
{

    Board board;

    Tetro tetro(1);
    tetro.current_location_x = 1;
    tetro.current_location_y = 20;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            std::cout << tetro.current_tetro[i][j];
        }
        std::cout << std::endl;
    }
    board.printBoard();
    std::cout << tetro.current_location_y << std::endl;


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
