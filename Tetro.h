#ifndef TETRO_H
#define TETRO_H

#include "Board.h"

class Tetro
{
public:
    Tetro(int blocktype);
    ~Tetro();
    enum {LEFT = 'l', DOWN = 'd', RIGHT = 'r'};
    bool moveTetro(char direction, Board & board);
    bool rotateTetro(Board board);
    bool collisionCheck(int potential[][2], Board board);
    int current_location_x, current_location_y;
    int ghost_location_x, ghost_location_y;
    int current_tetro[4][2];

private:
    int ghost_tetro[4][2];
    int tetro_shapes[7][4][2] =
    {
        // Z Block
        {{-1,-1},{0,-1},{0,0},{1,0}},

        // L Block
        {{-1,0}, {0,0}, {1,0}, {1,-1}},

        // O Block
        {{-1,-1}, {0,-1}, {-1,0}, {0,0}},

        //S Block
        {{0,-1}, {1,-1}, {-1,0}, {0,0}},

        // Line Block
        {{-2,0}, {-1,0}, {0,0}, {1,0}},

        // J Block
        {{-1,-1}, {-1,0}, {0,0}, {1,0}},

        //T Block
        {{0,-1}, {-1,0}, {0,0}, {1,0}},
    };

};
#endif
