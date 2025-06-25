#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>

#define N 3
#define WINDOW_TITLE "Tic Tac Toe"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define CELL_WIDTH (SCREEN_WIDTH/N)
#define CELL_HEIGHT (SCREEN_HEIGHT/N)

#define EMPTY 0
#define PLAYER_X 1
#define PLAYER_O 2

#define RUNNING_STATE 0
#define PLAYER_X_WON_STATE 1
#define PLAYER_O_WON_STATE 2
#define TIE_STATE 3
#define QUIT_STATE 4

typedef struct Game {
	SDL_Window *window;
	SDL_Renderer *renderer;
	int board[N*N];
	int player;
	int state;
} Game;

#endif //GAME_H_
