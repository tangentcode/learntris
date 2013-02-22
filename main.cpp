#include <iostream>
#include "grid.h"
#include <string>

using namespace std;



int main (int argc, char *argv())
{
    Grid x;
    x.initGrid();
    //prints grid
    for(int i = 0; i < 300; i++)
    {
        cout << *((*x.gridState) + i);
        if ((i+1)%25==0)
        {
            cout << endl;
        }
    }

}

