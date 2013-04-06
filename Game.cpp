#include "Game.h"







SDL_Surface* load_image(std::string filename)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    //SDL_Surface* optimizedImage = NULL;

    //Load the image
    //loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    //if( loadedImage != NULL )
    //{
        //Create an optimized surface
        loadedImage = SDL_DisplayFormat( IMG_Load( filename.c_str()) );

        //Free the old surface
        //SDL_FreeSurface( IMG_Load( filename.c_str()) );

        //If the surface was optimized
        //if( optimizedImage != NULL )
        //{
            //Color key surface
            SDL_SetColorKey( loadedImage, SDL_SRCCOLORKEY, SDL_MapRGB( loadedImage->format, 0, 0xFF, 0xFF ) );
        //}
    //}

    //Return the optimized surface
    return loadedImage;
}

void Game::imageBlitter( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Holds offsets
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, NULL, destination, &offset );
}



int Game::genBoard(Board board)
{
    for(int i = 0; i < 23; i++)
    {
        for(int k = 0; k < 12; k++)
        {
            //Checks and applies walls
            if(board.boardState[i][k] == 2)
            {
                int x = k*32;
                int y = i*32;
                imageBlitter(x,y,wall,screen);
            }
            //Checks and applies blocks
            else if (board.boardState[i][k] == 1)
            {
                int x = k*32;
                int y = i*32;
                imageBlitter(x,y,dead_block,screen);
            }
            else if (board.boardState[i][k] == 0)
            {
                int x = k*32;
                int y = i*32;
                imageBlitter(x,y,background,screen);
            }
        }
    }
}

void Game::gameLoop()
{
    Board board;
    Tetro tetro(rand() % 7);
    bool quit = false;
    bool pressflag = false;

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
                    tetro.moveTetro('u', board);
                    //locale.y=locale.y-32;
                    pressflag = true;
                    break;
                case SDLK_DOWN:
                    //direction = 'd';
                    tetro.moveTetro('d', board);

                    break;
                case SDLK_LEFT:
                    //direction = 'l';
                    tetro.moveTetro('l', board);
                    break;
                case SDLK_RIGHT:
                    //direction = 'r';
                    tetro.moveTetro('r', board);
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
            genBoard(board);
            //send pressflag waiting for input
            pressflag = false;
        }

        //Update the screen
        SDL_Flip( screen );
    }
}

Game::Game()
{
    SDL_Init( SDL_INIT_VIDEO );
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    SDL_WM_SetCaption( "learntris", NULL );
    background = load_image( "background.bmp" );
    live_block = load_image( "live.bmp" );
    wall = load_image( "wall.bmp" );
    dead_block = load_image("dead.bmp");
}

Game::~Game()
{
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( live_block );
    SDL_FreeSurface( screen );
    SDL_FreeSurface( wall );
    SDL_FreeSurface( dead_block );
    //Quit SDL
    SDL_Quit();
}




