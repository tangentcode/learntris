class Tetro
{
    public:
        Tetro();
        int location;
        void moveDown();
        void moveLeft();
        void moveRight();
        void rotateCounter();
        void rotateClock();
        int shapes[4][4];

};

Tetro::Tetro()
{

}

class Zblock : public Tetro
{
    public:
    Zblock();
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
Zblock::Zblock()
{
    int shape_init[16] = {-13,-12,0,1,-11,0,1,12,-13,-12,0,1,-11,0,1,12,};
    memcpy(shapes, shape_init, sizeof(shape_init));
};
