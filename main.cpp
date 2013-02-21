#include <iostream>
#include "grid.h"
#include <string>

using namespace std;



int main (int argc, char *argv())
{
    Grid x;
    x.initBoard();
    cout << x.gridState[0][2];
}

