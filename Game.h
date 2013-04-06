#ifndef GAME_H
#define GAME_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "Tetro.h"

const int SCREEN_WIDTH = 384;
const int SCREEN_HEIGHT = 768;
const int SCREEN_BPP = 32;

class Game
{
    public:
    Game();
    ~Game();
    SDL_Surface *background = NULL;
    SDL_Surface *live_block = NULL;
    SDL_Surface *wall = NULL;
    SDL_Surface *dead_block = NULL;
    SDL_Surface *screen = NULL;

    SDL_Event event;

    SDL_Surface* load_image(std::string filename);
    void imageBlitter(int x, int y, SDL_Surface * source, SDL_Surface * destination);
    bool load_files(std::string filename, std::string filename2, std::string filename3, std::string filename4);

    void gameLoop();
    void genBoard(Board board, Tetro tetro);
};

#endif
