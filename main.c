#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./game.h"
#include "./renderer.h"
#include "./logic.h"

bool sdl_initialize(Game *game) {
	if(SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return true;
	}

	game->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(!game->window) {
		fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
		return true;
	}

	game->renderer = SDL_CreateRenderer(game->window, -1, 0);
	if(!game->renderer) {
		fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
		return true;
	}

	return false;
}

void game_cleanup(Game *game, int EXIT_STATUS) {
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	SDL_Quit();
	exit(EXIT_STATUS);
}

int main() {
    Game game = {
        .window = NULL,
        .renderer = NULL,
        .board = {
            EMPTY, EMPTY, EMPTY,
            EMPTY, EMPTY, EMPTY,
            EMPTY, EMPTY, EMPTY
        },
        .player = PLAYER_X,
        .state = RUNNING_STATE
    };

    if (sdl_initialize(&game)) {
        game_cleanup(&game, EXIT_FAILURE);
    }

    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                game_cleanup(&game, EXIT_SUCCESS);
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
            	click_on_cell(&game, e.button.y / CELL_HEIGHT, e.button.x / CELL_WIDTH);
            }
        }

        SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
        SDL_RenderClear(game.renderer);
        render_game(&game);
        SDL_RenderPresent(game.renderer);

        SDL_Delay(16);
    }

    return 0;
}
