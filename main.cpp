#include "Tetro.h"
#include <iostream>
#include <ios>
#include "Game.h"

int main (int argc, char *argv[])
{
    Game game;
    game.gameLoop();





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
