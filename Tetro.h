#ifndef _Tetro_
#define _Tetro_

class Tetro
{
public:
    void moveTetro();
    bool collisionCheck();
    void rotateTetro();
    int current_location;
    int current_face;
    int current_tetro;
    int shape_tetro[7][4][4] =
    {
        {
            // Z Block
            {-13, -12, 0, 1},
            {-11, 0, 1, 12},
            {-1, 0, 12, 13},
            {-12, -1, 0, 11}
        },
        {
            // L Block
            {-12, 0, 12, 13},
            {-1, 0, 1, 11},
            {-13, -12, 0, 12},
            {-11, -1, 0, 1}
        },
        {
            // O Block
            {-13, -12, -1, 0},
            {-13, -12, -1, 0},
            {-13, -12, -1, 0},
            {-13, -12, -1, 0}
        },
        {
            //S Block
            {-12, -11, -1, 0},
            {-12, 0, 1, 13},
            {0, 1, 11, 12},
            {-13, -1, 0, 12}
        },
        {
            // Line Block
            {-23, -11, 1, 13},
            {10, 11, 12, 13},
            {-25, -13, -1, 11},
            {-14, -13, -12, -11}
        },
        {
            // J Block
            {-12, 0, 11, 12},
            {-13, -1, 0, 1},
            {-12, -11, 0, 12},
            {-1, 0, 1, 13}
        },
        {
            //T Block
            {-12, -1, 0, 1},
            {-12, 0, 1, 12},
            {-1, 0, 1, 12},
            {-12, -1, 0, 12}
        }
    };

private:

};


#endif
