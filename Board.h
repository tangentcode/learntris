#ifndef BOARD_H
#define BOARD_H

#include <cstring>
#include <iostream>

class Board
{
public:
    Board();
    ~Board();

    enum {BLOC_NULL, BLOC_FILL, BLOC_SIDE};
    int boardState[25][12];
    bool getSpace(int x);
    void initBoard();
    void printBoard();
    friend class Tetro;
};



#endif
