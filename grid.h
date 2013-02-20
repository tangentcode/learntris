#include <cstring>

class Grid
{
    public:
        void initBoard();
        bool gridState[10][20];
}

void Grid::initBoard (){
    memset((*this).gridState, false, sizeof((*this).gridState));
}
