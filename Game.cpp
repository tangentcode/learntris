#include "Game.h"

SDL_Surface* Game::load_image(std::string filename)
{

    SDL_Surface* loadedImage = NULL;
    loadedImage = SDL_DisplayFormat( IMG_Load( filename.c_str()) );
    //SDL_SetColorKey( loadedImage, SDL_SRCCOLORKEY, SDL_MapRGB( loadedImage->format, 0, 0xFF, 0xFF ) );
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

/*-------------------------------------------
Sets up the screen surface for flipping
--------------------------------------------*/


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
            //Background
            else if (board.boardState[i][k] == 0)
            {
                int x = k*32;
                int y = i*32;
                imageBlitter(x,y,background,screen);
            }
        }
    }
    //Renders current tetro
    for(int i =0; i <4; i++)
    {
        int blox = (tetro.current_location_x + tetro.current_tetro[i][0]) * 32;
        int bloy = (tetro.current_location_y + tetro.current_tetro[i][1]) * 32;
        imageBlitter(blox,bloy,live_block,screen);
    }
    //Renders current HUD and etc.
    imageBlitter(0,0,HUD,screen);
    for(int i =0; i <4; i++)
    {
        int blox = (preview[i][0] + 3) * 32;
        int bloy = (preview[i][1] + 1) * 32;
        imageBlitter(blox,bloy,dead_block,screen);
    }

    imageBlitter(16,8,TTF_RenderText_Shaded( font, "Next:", textColor , bgColor),screen);
    imageBlitter(192,8,TTF_RenderText_Shaded( font, str_stat.c_str(), textColor , bgColor),screen);
}
/*-------------------------------------------
Main game loop
--------------------------------------------*/

void Game::gameLoop()
{
    srand (time(NULL));
    Tetro tetro(rand() % 7);
    Tetro next_tetro(rand() % 7);
    int keydown_mark = 0;
    while( quit == false )
    {
        //Makes a new piece after the previous has been set
        if(piece_set == true)
        {
            Tetro new_tetro(rand() % 7);
            tetro = next_tetro;
            next_tetro = new_tetro;
            if(tetro.collisionCheck(tetro.current_tetro, board) == false)
            {
                quit = true;
            }
            memcpy(preview, next_tetro.current_tetro, sizeof(preview));
            piece_set = false;
        }

        //renders during events
        if( pressflag == true )
        {
            //Apply the background to the screen
            SDL_FillRect(screen, NULL, 0x000000);
            genBoard(board, tetro);
            //send pressflag waiting for input
            pressflag = false;
        }

        //Update the screen
        SDL_UpdateRect(screen,0,0,0,0);
        //SDL_Flip( screen );

        //Checks for input
        if( SDL_PollEvent( &event ) )
        {
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                switch( event.key.keysym.sym )
                {
                case SDLK_UP:
                    for(int i = 0; i < 22; i++)
                    {
                        while(piece_set == false)
                        {
                            for(int i =0; i <4; i++)
                            {
                                int blox = ((tetro.current_location_x + tetro.current_tetro[i][0] ) * 32);
                                int bloy = (tetro.current_location_y + tetro.current_tetro[i][1]) * 32;
                                imageBlitter(blox,bloy,live_block,screen);
                                SDL_UpdateRect(screen,0,0,0,0);
                            }
                            if(tetro.moveTetro('d', board) == false)
                            {
                                piece_set = true;
                            }
                        }

                    }
                    pressflag = true;
                    break;
                case SDLK_DOWN:
                    if(tetro.moveTetro('d', board) == false)
                    {
                        piece_set = true;
                    }
                    keydown_mark = SDL_GetTicks();
                    pressflag = true;
                    break;
                case SDLK_LEFT:
                    tetro.moveTetro('l', board);
                    keydown_mark = SDL_GetTicks();
                    pressflag = true;

                    break;
                case SDLK_RIGHT:
                    tetro.moveTetro('r', board);
                    keydown_mark = SDL_GetTicks();
                    pressflag = true;
                    break;
                case SDLK_z:
                    tetro.rotateTetro(board);
                    pressflag = true;
                }

            }

            //Quit
            else if( event.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        Uint8 *keystates = SDL_GetKeyState( NULL );
        if(keystates[SDLK_DOWN])
        {

            if(keydown_mark + 250 < SDL_GetTicks())
            {
                keydown_mark = SDL_GetTicks() -200;
                if(tetro.moveTetro('d', board) == false)
                {
                    piece_set = true;
                }
                genBoard(board, tetro);
            }

        }
        else if(keystates[SDLK_LEFT])
        {

            if(keydown_mark + 250 < SDL_GetTicks())
            {
                keydown_mark = SDL_GetTicks() -200;
                tetro.moveTetro('l', board);
                genBoard(board, tetro);
            }

        }
        else if(keystates[SDLK_RIGHT])
        {

            if(keydown_mark + 250 < SDL_GetTicks())
            {
                keydown_mark = SDL_GetTicks() -200;
                tetro.moveTetro('r', board);
                genBoard(board, tetro);
            }

        }
        if(board.lines_cleared > line_mark)
        {
            std::stringstream convert;
            convert << board.lines_cleared;
            str_stat = "Lines:" + convert.str();
            gravity -= (board.lines_cleared - line_mark) * 10;
            line_mark = board.lines_cleared;
        }
        //gravity
        if ((SDL_GetTicks() + gravity) > time_mark)
        {
            if(tetro.moveTetro('d', board) == false)
            {
                piece_set = true;
            }
            pressflag = true;
            time_mark = (SDL_GetTicks() + (gravity * 2));
        }
    }
}

Game::Game()
{
    SDL_Init( SDL_INIT_VIDEO );
    TTF_Init();
    screen = SDL_SetVideoMode( 384, 736, SCREEN_BPP, SDL_HWSURFACE);
    background = load_image( "media/background.bmp" );
    live_block = load_image( "media/live.bmp" );
    wall = load_image( "media/wall.bmp" );
    dead_block = load_image("media/dead.bmp");
    HUD = load_image("media/HUD.bmp");
    SDL_WM_SetCaption( "learntris", NULL );
    font = TTF_OpenFont( "media/DroidSans.ttf", 18 );
}

Game::~Game()
{
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( live_block );
    SDL_FreeSurface( screen );
    SDL_FreeSurface( wall );
    SDL_FreeSurface( dead_block );
    SDL_FreeSurface( HUD );
    TTF_CloseFont( font );
    //Quit SDL
    SDL_Quit();
}
