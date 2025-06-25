#include "./game.h"
#include "./logic.h"

void switch_player(Game *game) {
	if(game->player == PLAYER_X) {
		game->player = PLAYER_O;
	} else {
		game->player = PLAYER_X;
	}
}

int check_player_won(Game *game, const int player) {
	int row_count = 0;
	int column_count = 0;
	int diag1_count = 0;
	int diag2_count = 0;
	
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			if(game->board[i*N+j] == player) {
				row_count++;
			} 
			if(game->board[j*N+i] == player) {
				column_count++;
			}
		}
		if(row_count >= N || column_count >= N) {
			return 1;
		}
		
		column_count = 0;
		row_count = 0;
		
		if(game->board[i*N+i] == player) {
			diag1_count++;
		} 
		if(game->board[i*N+N-i-1] == player) {
			diag2_count++;
		}
	}
	
	return diag1_count >= N || diag2_count >= N;
}

void reset_game(Game *game) {
	game->player = PLAYER_X;
	game->state = RUNNING_STATE;
	for(int i=0;i<N*N;i++) {
		game->board[i] = EMPTY;
	}
}

int count_cells(const int *board) {
	int count = 0;
	
	for(int i=0;i<N*N;i++) {
		if(board[i] == EMPTY) {
			count++;
		}
	}
	
	return count;
}

void game_over_condition(Game *game) {
	if(check_player_won(game, PLAYER_X)) {
		game->state = PLAYER_X_WON_STATE;
	} else if(check_player_won(game, PLAYER_O_WON_STATE)) {
		game->state = PLAYER_O_WON_STATE;
	} else if(count_cells(game->board) == 0) {
		game->state = TIE_STATE;
	}
}

void player_turn(Game *game, int row, int column) {
	if(game->board[row*N+column] == EMPTY) {
		game->board[row*N+column] = game->player;
		switch_player(game);
		game_over_condition(game);
	}
}

void click_on_cell(Game *game, int row, int column) {
	if(game->state == RUNNING_STATE) {
		player_turn(game, row, column);
	} else {
		reset_game(game);
	}
}
