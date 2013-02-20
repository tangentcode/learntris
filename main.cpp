#include <iostream>
#include "Grid.h"

using namespace std;


int main ()
{
    Grid x;
    x.initBoard();
    cout << x.gridState[0][2];
}
