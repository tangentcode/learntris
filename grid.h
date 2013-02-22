#include <cstring>

class Grid
{
    public:
        bool gridState[12][25];
        void initGrid();
        friend class Tetronimo;
};

void Grid::initGrid()
{
    memset((*this).gridState, false, sizeof(*this).gridState);
    //builds true value walls during grid initialization
    // doesnt work...?

    for (int i = 0; i < 11; i++)
    {
        (*this).gridState[i][0] = true;

    }
    for (int i = 0; i < 25; i++)
    {
        (*this).gridState[0][i] = true;
        (*this).gridState[11][i] = true;
    }

}
