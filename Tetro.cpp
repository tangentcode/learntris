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
/*---------------------------------
CONVERT ME TO SWITCH CASE!
-----------------------------------*/
bool Tetro::rotateTetro(Board board)
{
    //temporary holders for switching
    int sX, sY;
    for(int i = 0; i<4; i++)
    {
        //Store the numbers, change the operand of the y value, switch
        sX = current_tetro[i][0];
        sY = current_tetro[i][1];
        sY = sY * (-1);
        ghost_tetro[i][0] = sY;
        ghost_tetro[i][1] = sX;
    }
    if(collisionCheck(ghost_tetro, board))
    {
        memcpy(current_tetro, ghost_tetro, sizeof(current_tetro));
        /*for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                current_tetro[i][j] = ghost_tetro[i][j];
            }
            //std::cout << current_tetro[i][0] << current_tetro[i][1] << std::endl;
        }*/
    }
    else
    {
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

bool Tetro::moveTetro(char direction, Board & board)
{
    int sX, sY;
    switch(direction)
        {
        case DOWN:
            ghost_location_y = current_location_y; break;
        case LEFT:
            ghost_location_x = current_location_x; break;
        case RIGHT:
            ghost_location_x = current_location_x; break;
        }
    for(int i = 0; i<4; i++)
    {
        /*-------------------------------------
        Note to self: Need to get rid of the memcpy
        in this, that's not the  purpose of moving
        left and right. Replace it with a changed
        'current_location_x/y' or something.
        Also, convert to switch case later.
        -------------------------------------*/
        switch(direction)
        {
        case DOWN:
            sY = current_tetro[i][1];
            sY++;
            ghost_tetro[i][1] = sY;
            ghost_tetro[i][0] = current_tetro[i][0];
            break;
        case LEFT:
            sX = current_tetro[i][0];
            sX--;
            ghost_tetro[i][0] = sX;
            ghost_tetro[i][1] = current_tetro[i][1];
            break;
        case RIGHT:
            sX = current_tetro[i][0];
            sX++;
            ghost_tetro[i][0] = sX;
            ghost_tetro[i][1] = current_tetro[i][1];
            break;
        }

    }
    if(collisionCheck(ghost_tetro, board))
    {
        if(direction == DOWN)
        {
            current_location_x = ghost_location_x;
        }
        else
        {
            current_location_y = ghost_location_y;
        }
    }
    else if(direction == 'd')
    {
        std::cout << "written" << std::endl;
        board.writeToBoard(current_location_x, current_location_y, current_tetro);
        return false;
    }
    else
    {
        return false;
    }
    return true;
}
