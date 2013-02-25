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

    int location = 150;
        for (int j = 0; j < 112; j++)
        {
            *((*x.boardState) + (location + *((*z.shapes) + j))) = 8;
            if ((j+1)% 4 == 0)
            {
                x.printBoard();
                x.initBoard();
                cout << endl << "i =" << j << endl;
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
