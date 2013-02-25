class Tetro
{
    public:
        int location;
        void moveDown();
        void moveLeft();
        void moveRight();
        void rotateCounter();
        void rotateClock();
        //Z,L,O,S,I,J,T
        int shapes[7][16] = {{-13,-12,0,1,-11,0,1,12,-1,0,12,13,-12,-1,0,11},
        {-12,0,12,13,-1,0,1,11,-11,-12,0,12,-11,-1,0,1},
        {-12,-11,-1,0,-12,-11,-1,0,-12,-11,-1,0,-12,-11,-1,0},
        {-12,-11,-1,0,-12,0,1,13,0,1,11,12,-11,-1,0,12},
        {-23,-11,1,13,10,11,12,13,-25,-13,11,23,-14,-12,-11,-10},
        {-12,0,11,12,-13,-1,0,1,-12,-11,0,12,-1,0,1,13},
        {-12,-1,0,1,-12,0,1,12,-1,0,1,12,-12,-1,0,12}};

};

class Zblock : public Tetro
{

};
class Lblock : public Tetro
{

};
class Oblock : public Tetro
{

};
class Sblock : public Tetro
{

};
class Iblock : public Tetro
{

};
class Jblock : public Tetro
{

};
class Tblock : public Tetro
{

};
