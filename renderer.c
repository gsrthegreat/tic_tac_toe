#include "./game.h"
#include "./renderer.h"

const SDL_Color GRID_COLOR = { .r = 255, .g = 255, .g = 255 };
const SDL_Color PLAYER_X_COLOR = { .r = 100, .g = 50, .g = 50 };
const SDL_Color PLAYER_O_COLOR = { .r = 50, .g = 100, .g = 255 };
const SDL_Color TIE_COLOR = { .r = 100, .g = 100, .g = 100 };

void render_grid(SDL_Renderer *renderer, const SDL_Color *color) {
	SDL_SetRenderDrawColor(renderer, color->r, color->b, color->g, 255);
	for(int i=1;i<N; ++i) {
		SDL_RenderDrawLine(renderer, i*CELL_WIDTH, 0, i*CELL_WIDTH, SCREEN_HEIGHT);
		SDL_RenderDrawLine(renderer, 0, i*CELL_HEIGHT, SCREEN_WIDTH, i*CELL_HEIGHT);
	}
}

void render_x(SDL_Renderer *renderer, int row, int column, const SDL_Color *color) {
	const float half_box_size = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
	const float center_x = 0.5 * CELL_WIDTH + column * CELL_WIDTH;
	const float center_y = 0.5 * CELL_HEIGHT + row * CELL_HEIGHT;
	
	thickLineRGBA(renderer, center_x + half_box_size, center_y + half_box_size, center_x - half_box_size, center_y - half_box_size, 10, color->r, color->g, color->b, 255);
	thickLineRGBA(renderer, center_x + half_box_size, center_y - half_box_size, center_x - half_box_size, center_y + half_box_size, 10, color->r, color->g, color->b, 255);
}

void render_o(SDL_Renderer *renderer, int row, int column, const SDL_Color *color) {
	const float half_box_size = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
	const float center_x = 0.5 * CELL_WIDTH + column * CELL_WIDTH;
	const float center_y = 0.5 * CELL_HEIGHT + row * CELL_HEIGHT;
	
	filledCircleRGBA(renderer, center_x, center_y, half_box_size + 5, color->r, color->g, color->b, 255);
	filledCircleRGBA(renderer, center_x, center_y, half_box_size - 5, 0, 0, 0, 255);
}

void render_board(Game *game, const SDL_Color *player_x_color, const SDL_Color *player_o_color) {
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			switch(game->board[i*N+j]) {
				case PLAYER_X:
					render_x(game->renderer, i, j, player_x_color);
					break;
				case PLAYER_O:
					render_o(game->renderer, i, j, player_o_color);
					break;
				default:
					{}
			}
		}
	}
}

void render_running_state(Game *game) {
	render_grid(game->renderer, &GRID_COLOR);
	render_board(game, &PLAYER_X_COLOR, &PLAYER_O_COLOR);
}

void render_game_over_state(Game *game, const SDL_Color *color) {
	render_grid(game->renderer, color);
	render_board(game, color, color);
}

void render_game(Game *game) {
	switch(game->state) {
		case RUNNING_STATE:
			render_running_state(game);
			break;
		case PLAYER_X_WON_STATE:
			render_game_over_state(game, &PLAYER_X_COLOR);
			break;
		case PLAYER_O_WON_STATE:
			render_game_over_state(game, &PLAYER_O_COLOR);
			break;
		case TIE_STATE:
			render_game_over_state(game, &TIE_COLOR);
			break;
		default: 
			{}
	}
}
