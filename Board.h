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
    int boardState[23][12];
    bool getSpace(int x);
    void initBoard();
    void printBoard();
    void writeToBoard(int locX, int locY, int shape_to_write[][2]);
    void checkBoard(Board board);
};



#endif
