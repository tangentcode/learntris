#include <cstring>
class Grid
{
    public:
        bool gridState[10][10];
        void initGrid();
        friend class Tetronimo;
};

void Grid::initGrid()
{
    memset((*this).gridState, false, sizeof(*this).gridState);
}
