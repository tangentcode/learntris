#include <iostream>
#include <string>
#include "Tetro.h"
#include "Board.h"

using namespace std;

void pFunction(Board board);
void gFunction(Board *board);

main()
{
    string line;
    string lastline;
    Board overboard;
    Board * p_overboard = &overboard;
    while(line != "q")
    {
        cout << ">";
        cin >> line;
        if(line == "g")
        {
            gFunction(p_overboard);
        }
        if(line == "p")
        {
            pFunction(overboard);
        }
        lastline = line;
    }
}

void pFunction(Board board)
{
            for (int k=0; k< 300; k++)
            {
                if(*((*board.boardState) + k) == 2)
                {
                }
                else if(k<48)
                {
                    std::cout << " ";
                }

                else if(*((*board.boardState) + k) == 1)
                {
                    std::cout << "X";
                }
                else if(*((*board.boardState) + k) == 0)
                {
                    std::cout << ".";
                }
                if ((k+1)%12 == 0)
                {
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;
};

void gFunction(Board *board)
{
    for (int k=0; k< 300; k++)
    {
        if(*((*board->boardState) + k) == 2)
        {
        }
        else if(*((*board->boardState) + k) == 0)
        {
            cin >> (*((*board->boardState) + k));
        }
        if ((k+1)%12 == 0)
        {
            std::cout << std::endl;
            for(int i = 0; i < 12; i++)
            {
                cout << (*((*board->boardState) + ((k - 11) + i) ));
            }
        }
    }
    std::cout << std::endl;
};
