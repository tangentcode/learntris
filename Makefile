all:
	g++ -o learntris main.cpp Board.cpp Board.h Tetro.cpp Tetro.h Game.h Game.cpp -lSDL -lSDL_image -std=gnu++11
