/**
 *  @file Tetronimo.h
 *  @brief Define enumerated type "facing" and Tetronimo class (template)
 *  @author Chance Rosenthal, Jan Frozsak
 */


using namespace std;

enum facing {UP, DOWN, LEFT, RIGHT};

class Tetronimo
{
    public:
        //Tetronimo();
        //~Tetronimo();

    /*----------------------------/
     * Declare rotation functions /
     *---------------------------*/
        void rotateClockwise();
        void rotateCounterClockwise();
        void wallBumpClockwise();
        void wallBumpCounterClockwise();
        bool canRotate(bool);   // NOTE: clockwise will be represented by TRUE and counterclockwise by FALSE to avoid another enum.
                                // If this function returns 0, it should result in a wall bump.
    /*----------------------------/
     * Declare location functions /
     *---------------------------*/
        facing isFacing();
        void getAnchorLoc(int&,int&);
        void collisionCheck();
    /*------------------------/
     * Declare grid functions /
     *-----------------------*/
        void getGridState(Grid current);
        bool flashGrid[10][20];
        int location; //a single number representing the offset of the anchor block
                      //from 0 on the grid
    /*------------------------/
     * Declare move functions /
     *-----------------------*/
        void moveLeft();
        void moveRight();
        void moveDown();
        //experimental stuff//
        int m_face[4];
        void initAnchor();
        void printToTest();

    protected:
        int m_brickLocs[4][4];

    private:
        facing m_facing;
};

void Tetronimo::getGridState(Grid current)
{
    //loads all of grid into local grid for collision detection
    memcpy((*this).flashGrid, current.gridState, sizeof(current.gridState));
}

void Tetronimo::initAnchor()
{
    (*this).location = 125;
}

void Tetronimo::printToTest()
{
    *((*(*this).flashGrid) + (*this).location) = true;
}

class LineBlock : public Tetronimo
{
};

