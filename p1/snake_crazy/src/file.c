#include "file.h"
#include <stdio.h>
#include <stdlib.h>

const char dn[] = "ESWN";

game_t *create_game(const char *file_name) {
  game_t* game = (game_t*)malloc(sizeof(game_t));
  char buf[1024];
  int n, m, i, j, k;
  FILE* fp = fopen(file_name, "r");
  fscanf(fp, "%d%d", &n, &m);
  game->board = create_board(n, m);
  fscanf(fp, "%f%f%d", &game->time_step, &game->food_probability, &game->growth_per_food);
  for (i = 0; i < n; i++) {
    fscanf(fp, "%s", buf);
    for (j = 0; j < m; j++) {
      if (buf[j] == '-') {
        *board_cell(game->board, i, j) = CELL_OPEN;
      } else if (buf[j] == 'X') {
        *board_cell(game->board, i, j) = CELL_WALL;
      } else if (buf[j] >= 'A' && buf[j] <= 'Z'){
        for (k = 0; k < 4; k++) {
          if (dn[k] == buf[j]) {
            game->snake1 = create_snake(game->board, i, j, (direction_t)k);
          }
        }
      } else {
        for (k = 0; k < 4; k++) {
          if ((dn[k] ^ 32) == buf[j]) {
            game->snake2 = create_snake(game->board, i, j, (direction_t)k);
          }
        }
      }
    }
  }
  fclose(fp);
  return game;
}

void destroy_game(game_t *game) {
  destroy_board(game->board);
  destroy_snake(game->snake1);
  destroy_snake(game->snake2);
  free(game);
}
