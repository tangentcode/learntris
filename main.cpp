/*
 * File:   main.cpp
 * Author: x
 *
 * Created on March 6, 2013, 5:10 AM
 */

//#include <cstdlib>
#include <iostream>
#include "Tetro.h"
#include "Board.h"
//#include "Game.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDLStuff.h"

using namespace std;
/*
void printTetros(Board x, Tetro z)
{
    cout << "got here";
    int location = 56;
    for (int i = 0; i < 48; i++)
    {
        *((*x.boardState)+ (location + z.shape_tetro[0][0][i])) = true;
        if ((i+1)%4 == 0)
        {
            cout << endl;
            x.printBoard();
            x.boardSetup();
        }
    }
}
*/

/*------------------------------------
Pushes the current board to the screen
------------------------------------*/
int genBoard(Board board)
{
    for(int i = 0; i < 25; i++)
    {
        for(int k = 0; k < 12; k++)
        {
            //Checks and applies walls
            if(board.boardState[i][k] == 2)
            {
                int x = k*32;
                int y = i*32;
                apply_surface(x,y,wall,screen);
            }
            //Checks and applies blocks
            else if (board.boardState[i][k] == 1)
            {
                int x = k*32;
                int y = i*32;
                apply_surface(x,y,anchor,screen);
            }
        }
    }
}


int main(int argc, char** argv)
{
    Board board1;
    board1.initBoard();
    Tetro tetro1;
    tetro1.current_location = 186;
    tetro1.current_tetro = 0;
    tetro1.current_face = 0;
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files("background.png", "tile3.bmp", "wall.bmp")== false )
    {
        return 1;
    }

    SDL_FillRect(screen, NULL, 0x000000);
    SDL_Rect locale;
    locale.x=160;
    locale.y = 448;
    bool pressflag = false;
    genBoard(board1);
    char direction;

    while( quit == false )
    {
        //If there's an event to handle
        if( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event.key.keysym.sym )
                {
                case SDLK_UP:
                    tetro1.current_location-=12;
                    locale.y=locale.y-32;
                    pressflag = true;
                    break;
                case SDLK_DOWN:
                    direction = 'd';
                    if(tetro1.collisionCheck(direction, board1))
                    {
                        tetro1.current_location+=12;
                        locale.y=locale.y+32;
                        pressflag = true;
                    }

                    break;
                case SDLK_LEFT:
                    direction = 'l';
                    if(tetro1.collisionCheck(direction, board1) == true)
                    {
                        tetro1.current_location--;
                        locale.x=locale.x-32;
                        pressflag = true;
                    }
                    break;
                case SDLK_RIGHT:
                    direction = 'd';
                    if(tetro1.collisionCheck(direction, board1))
                    {
                        tetro1.current_location++;
                        locale.x=locale.x+32;
                        pressflag = true;
                    }
                    break;
                }

            }

            //If the user has Xed out the window
            else if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
                pressflag = false;
            }
        }

        //If a message needs to be displayed
        if( pressflag == true )
        {
            //Apply the background to the screen
            SDL_FillRect(screen, NULL, 0x000000);
            genBoard(board1);
            apply_surface( locale.x, locale.y, anchor, screen );
            //send pressflag waiting for input
            pressflag = false;
        }

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
    }




    apply_surface( 0, 0, background, screen );

    clean_up();



    return 0;
}






