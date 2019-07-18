#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char grid[] = " +X*";
int a[105][105];

void display(game_t *game) {
  system("clear");
  board_t *board = game->board;
  memset(a, 0, sizeof(a));
  {
    snake_node_t* p = game->snake1->head;
    while (p) {
      a[p->row][p->col] = 1;
      p = p->next;
    }
    p = game->snake2->head;
    while (p) {
      a[p->row][p->col] = 2;
      p = p->next;
    }
  }
  for (int i = 0; i < board->rows; i++) {
    for (int j = 0; j < board->cols; j++) {
      if (game->snake1->head->row == i && game->snake1->head->col == j) {
        printf("H ");
      } else if (game->snake2->head->row == i && game->snake2->head->col == j) {
        printf("Z ");
      } else if (a[i][j] == 1) {
        printf("a ");
      } else if (a[i][j] == 2) {
        printf("b ");
      } else {
        printf("%c ", grid[*board_cell(board, i, j)]);
      }
    }
    puts("");
  }
}
