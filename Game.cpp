#include "Game.h"







SDL_Surface* Game::load_image(std::string filename)
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



void Game::genBoard(Board board, Tetro tetro)
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
    for(int i =0; i <4; i++)
    {
        int blox = (tetro.current_location_x + tetro.current_tetro[i][0]) * 32;
        int bloy = (tetro.current_location_y + tetro.current_tetro[i][1]) * 32;
        imageBlitter(blox,bloy,live_block,screen);
    }


}

void Game::gameLoop()
{
    Board board;
    Tetro tetro(4);
    bool quit = false;
    bool pressflag = true;
    bool piece_set = true;

    while( quit == false )
    {
        if(piece_set == true)
        {
            int piece = rand() % 7;
            Tetro next_tetro(piece);
            tetro = next_tetro;
            piece_set = false;
        }
        if( pressflag == true )
        {
            //Apply the background to the screen
            SDL_FillRect(screen, NULL, 0x000000);
            genBoard(board, tetro);
            //send pressflag waiting for input
            pressflag = false;
        }

        //Update the screen
        SDL_Flip( screen );
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
                    tetro.current_location_y--;
                    //tetro.moveTetro('u', board);
                    //locale.y=locale.y-32;
                    pressflag = true;
                    break;
                case SDLK_DOWN:
                    if(tetro.moveTetro('d', board) == false)
                    {
                        piece_set = true;
                    }
                    pressflag = true;
                    break;
                case SDLK_LEFT:
                    //direction = 'l';
                    tetro.moveTetro('l', board);
                    pressflag = true;
                    break;
                case SDLK_RIGHT:
                    //direction = 'r';
                    tetro.moveTetro('r', board);
                    pressflag = true;
                    break;
                case SDLK_z:
                    tetro.rotateTetro(board);
                    pressflag = true;
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

    }
}

Game::Game()
{
    SDL_Init( SDL_INIT_VIDEO );
    screen = SDL_SetVideoMode( 384, 736, SCREEN_BPP, SDL_SWSURFACE );
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




