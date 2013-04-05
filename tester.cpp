#include <iostream>
#include <string>
#include "Tetro.h"
#include "Board.h"

using namespace std;

void pFunction(Board board);
void gFunction(Board &board);

main()
{
    string line;
    string lastline;
    Board overboard;
    //Board * p_overboard = &overboard;
    while(line != "q")
    {
        cout << ">";
        cin >> line;
        if(line == "g")
        {
            gFunction(overboard);
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
            for (int k=0; k< 276; k++)
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

void gFunction(Board &board)
{
    char line[10];
    for (int i=0; i< 22; i++)
    {
            cin >> line;
            for(int k = 0; k < 12; k++)
            {
                if((k!=0) && (k!=11))
                {
                    int temp = line[k] - '0';
                    board.boardState[i][k] = temp;
                    std::cout << board.boardState[i][k] << " " << temp << std::endl;
                }
            }
        }
        std::cout << std::endl;
};
