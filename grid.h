#include <cstring>
class Grid
{
    public:
        bool gridState[10][22];
        void initGrid();
        friend class Tetronimo;
};

void Grid::initGrid()
{
    memset((*this).gridState, false, sizeof(*this).gridState);
    for (int i; i < 10; i++)
    {
        (*this).gridState[0][i] = true;
    }
}
