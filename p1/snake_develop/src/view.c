#include "view.h"
#include <stdio.h>
#include <stdlib.h>

const char grid[] = "-+X*";

void display(game_t *game) {
    system("clear");
    board_t *board = game->board;
    int i, j;
    for (i = 0; i < board->rows; i++) {
        for (j = 0; j < board->cols; j++) {
            printf("%c", grid[*board_cell(board, i, j)]);
        }
        puts("");
    }
}
