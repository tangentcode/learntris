#include "Tetro.h"
#include "Game.h"

int main (int argc, char *argv[])
{
    Game game;
    game.gameLoop();
    std::cout << "Game Over!" << std::endl;
    return 0;
}
