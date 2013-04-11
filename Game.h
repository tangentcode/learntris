#ifndef GAME_H
#define GAME_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include "Tetro.h"
#include <time.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    SDL_Surface *HUD = NULL;
    SDL_Event event;
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Color bgColor = { 0,0,0 };
    TTF_Font *font = NULL;


    Board board;
    bool quit = false;
    bool pressflag = true;
    bool piece_set = true;
    int gravity = 1000;
    int time_mark = 0;
    int line_mark = 0;
    int keydown_mark = 0;
    int preview[4][2];
    int pause = 1;
    std::string str_stat;


    SDL_Surface* load_image(std::string filename);
    void imageBlitter(int x, int y, SDL_Surface * source, SDL_Surface * destination);

    void gameLoop();
    void genBoard(Board board, Tetro tetro);
    bool checkLoss(Board board);
};

#endif
