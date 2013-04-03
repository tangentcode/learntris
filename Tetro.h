#ifndef TETRO_H
#define TETRO_H

#include "Board.h"

class Tetro
{
public:
    Tetro(int blocktype);
    ~Tetro();
    void moveTetro(char direction, Board board);
    void rotateTetro(Board board);
    bool collisionCheck(int potential[][2], Board board);
    int current_location_x, current_location_y;
    int current_tetro[4][2];

private:
    int tetro_shapes[7][4][2] =
    {
        // Z Block
        {{-1,-1},{0,-1},{0,0},{1,0}},

        // L Block
        {{0,-1}, {0,0}, {0,1}, {1,1}},

        // O Block
        {{-1,-1}, {0,-1}, {-1,0}, {0,0}},

        //S Block
        {{0,-1}, {1,-1}, {-1,0}, {0,0}},

        // Line Block
        {{1,-2}, {1,-1}, {1,0}, {1,1}},

        // J Block
        {{0,-1}, {0,0}, {1,-1}, {0,-1}},

        //T Block
        {{0,-1}, {-1,0}, {0,0}, {-1,0}},
    };

};



#endif
