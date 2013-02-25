#include <iostream>
#include "Board.h"
#include "Tetro.h"

using namespace std;

int main()
{
    Tetro z;
    Board x;
    /*for (int i=0; i< 7*16; i++)
    {

        cout << *((*z.shapes) + i) <<endl;
    }*/


    for (int i = 0; i < 4; i++)
    {
        int what = 0;
        for (int j=0; j<4; j++)
        {
            const int location = 150;
            *((*x.boardState) + (location + *((*z.shapes) + i))) = 8;
            if (j == 3)
            {
                x.printBoard();
                x.initBoard();
            }
        }
    }
}
/* remember, we dont need to store the tetronimo on the grid at all,
just change it's value. It will call the grid whenever it moves to verify it can,
but it doesnt need to be stored there everytime; just stored as an int(which is
actually an offset from 0).

The piece will call Board.getSpace(this may not even be necessary) to check if the
space it's about to 'enter' is empty for each block, then offset it's 'location' by
required value.

Note to self, dont leave the Z block constructor like that. maybe have the constructor
of Tetro grab from somewhere, and have the children inherit that with cpp11*/
