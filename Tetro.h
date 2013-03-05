class Tetro
{
    public:
        int location;
        bool moveDown(int& locale, Board thisboard);
        bool moveLeft(int& locale, Board thisboard);
        bool moveRight(int& locale, Board thisboard);
        void rotateCounter();
        void rotateClock();
        //Z,L,O,S,I,J,T
        int shapes[7][4][4] = {{{-13,-12,0,1},{-11,0,1,12},{-1,0,12,13},{-12,-1,0,11}},
        {{-12,0,12,13},{-1,0,1,11},{-13,-12,0,12},{-11,-1,0,1}},
        {{-13,-12,-1,0},{-13,-12,-1,0},{-13,-12,-1,0},{-13,-12,-1,0}},
        {{-12,-11,-1,0},{-12,0,1,13},{0,1,11,12},{-13,-1,0,12}},
        {{-23,-11,1,13},{10,11,12,13},{-25,-13,-1,11},{-14,-13,-12,-11}},
        {{-12,0,11,12},{-13,-1,0,1},{-12,-11,0,12},{-1,0,1,13}},
        {{-12,-1,0,1},{-12,0,1,12},{-1,0,1,12},{-12,-1,0,12}}};
        int currentshape;
        int shapeface;
        friend class Board;

};

bool Tetro::moveLeft(int& locale, Board thisboard)
{
    for (int i = 0; i < 4; i++)
    {
        if (thisboard.getSpace((locale -1)+shapes[currentshape][shapeface][i]))
        {
            std::cout << "nope";
            return false;

        }
        else if (i == 3)
        {
            int * loc = &locale;
            *loc = locale--;
            return true;
        }

    }

};

bool Tetro::moveRight(int& locale, Board thisboard)
{
    for (int i = 0; i < 4; i++)
    {
        if (thisboard.getSpace((locale + 1)+shapes[currentshape][shapeface][i]))
        {
            std::cout << "nope";
            return false;

        }
        else if (i == 3)
        {
            int * loc = &locale;
            *loc = locale++;
            return true;
        }

    }

};

bool Tetro::moveDown(int& locale, Board thisboard)
{
    for (int i = 0; i < 4; i++)
    {
        if (thisboard.getSpace((locale + 12)+shapes[currentshape][shapeface][i]))
        {
            std::cout << "nope";
            break;

        }
        else if (i == 3)
        {
            int * loc = &locale;
            *loc = locale + 12;
            return true;
        }

    }

};
