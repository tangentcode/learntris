#include <cstring>
class Board
{
    public:
        Board();

        enum {BLOC_NULL, BLOC_FILL, BLOC_SIDE};
        int boardState[12][25];
        bool getSpace(int x);
        int test = 4;
};

Board::Board()
{
    memset(boardState, BLOC_NULL, sizeof(boardState));
}

bool Board::getSpace(int x)
{
    if (*((*boardState) + x) != BLOC_NULL)
    {
        return true;
    }
    else
    {
        return false;
    }

}
