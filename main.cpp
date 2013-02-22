#include <iostream>
#include "grid.h"
#include <string>
#include "Tetronimo.h"

using namespace std;



int main (int argc, char *argv())
{
    Grid x;
    x.initGrid();
    Tetronimo t;
    t.getGridState(x);
    t.initAnchor();
    t.printToTest();



    //prints grid
    for(int i = 0; i < 300; i++)
    {
        cout << *((*t.flashGrid) + i) <<endl;/*
        if ((i+1)%25==0)
        {
            cout << endl;
        }*/
    }

}

