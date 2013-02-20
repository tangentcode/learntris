/**
 *  @file Tetronimo.h
 *  @brief Define enumerated type "facing" and Tetronimo class (template)
 *  @author Chance Rosenthal, Jan Frozsak
 */

#ifndef TETRONIMO_H_INCLUDED
#define TETRONIMO_H_INCLUDED

using namespace std;

enum facing {UP, DOWN, LEFT, RIGHT}

Class Tetronimo
{
    public:
        Tetronimo();
        ~Tetronimo();

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

    protected:
        int m_brickLocs[4][4];

    private:
        facing m_facing;
};

#endif // TETRONIMO_H_INCLUDED
