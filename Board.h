#include <cstring>
class Board
{
    public:
        Board();

        enum {BLOC_NULL, BLOC_FILL, BLOC_SIDE};
        int boardState[25][12];
        bool getSpace(int x);
        void initBoard();
        void printBoard();
};

Board::Board()
{
    memset(boardState, BLOC_NULL, sizeof(boardState));
}

void Board::initBoard()
{
    memset(boardState, BLOC_NULL, sizeof(boardState));
    for (int i = 0; i < 25; i++)
    {
        boardState[i][0] = 2;
        boardState[i][11] = 2;
    }
    for(int i = 0; i < 12; i++)
    {
        boardState[24][i] = 2;
    }
}

void Board::printBoard()
{
    for (int k=0; k< 300; k++)
    {
        std::cout << *((*boardState) + k);
        if ((k+1)%12 == 0)
        {
        std::cout << std::endl;
        }
    }
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
