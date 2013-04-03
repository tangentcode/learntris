#include "Tetro.h"
#include <iostream>
#include <cstring>

Tetro::Tetro(int blocktype)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            current_tetro[i][j] = tetro_shapes[blocktype][i][j];
        }
    }
};

Tetro::~Tetro()
{

};

void Tetro::rotateTetro(Board board)
{
    //temporary holders for switching
    int sX, sY;
    int potential_tetro[4][2];
    for(int i = 0; i<4; i++)
    {
        //Store the numbers, change the operand of the y value, switch
        sX = current_tetro[i][0];
        sY = current_tetro[i][1];
        sY = sY * (-1);
        potential_tetro[i][0] = sY;
        potential_tetro[i][1] = sX;
    }
    if(collisionCheck(potential_tetro, board))
    {
        std::cout << "rotated";
        memcpy(current_tetro, potential_tetro, sizeof(current_tetro));
        /*for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                current_tetro[i][j] = potential_tetro[i][j];
            }
            //std::cout << current_tetro[i][0] << current_tetro[i][1] << std::endl;
        }*/
    }
    else
    {
        std::cout << "not rotated";
    }
}

bool Tetro::collisionCheck(int potential[][2], Board board)
{
    int pot_x, pot_y;
    for(int i = 0; i < 4; i++)
    {
        pot_x = potential[i][0] + current_location_x;
        pot_y = potential[i][1] + current_location_y;

        //boardState is y,x
        if (board.boardState[pot_y][pot_x] !=0)
        {
            return false;
            break;
        }
    }
    return true;
}

void Tetro::moveTetro(char direction, Board board)
{
    int sX, sY;
    int potential_tetro[4][2];
    // down
    for(int i = 0; i<4; i++)
    {
        /*-------------------------------------
        Note to self: Need to get rid of the memcpy
        in this, that's not the  purpose of moving
        left and right. Replace it with a changed
        'current_location_x/y' or something.
        -------------------------------------*/
        if(direction == 'd')
        {
            sY = current_tetro[i][1];
            sY++;
            potential_tetro[i][1] = sY;
            potential_tetro[i][0] = current_tetro[i][0];
        }
        else if(direction == 'r')
        {
            sX = current_tetro[i][0];
            sX++;
            potential_tetro[i][0] = sX;
            potential_tetro[i][1] = current_tetro[i][1];

        }
        else if(direction == 'l')
        {
            sX = current_tetro[i][0];
            sX--;
            potential_tetro[i][0] = sX;
            potential_tetro[i][1] = current_tetro[i][1];

        }
    }
    if(collisionCheck(potential_tetro, board))
    {
        memcpy(current_tetro, potential_tetro, sizeof(current_tetro));
    }
    else
    {
    }
}
