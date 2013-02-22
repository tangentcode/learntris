#include <cstring>
class Grid
{
    public:
<<<<<<< HEAD
        bool gridState[10][22];
=======
        bool gridState[10][20];
>>>>>>> 16a64fb291f355587eb9cd57e266de762a5d978b
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
