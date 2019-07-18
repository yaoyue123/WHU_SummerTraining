#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const static int dx[] = {0, 1, 0, -1};
const static int dy[] = {1, 0, -1, 0};

board_t *create_board(int rows, int cols) {
  board_t *board = (board_t *)malloc(sizeof(board_t));
  board->rows = rows;
  board->cols = cols;
  board->cells = (cell_t *)malloc(sizeof(cell_t) * rows * cols);
  memset(board->cells, 0, sizeof(cell_t) * rows * cols);
  return board;
}

void destroy_board(board_t *board) {
  free(board->cells);
  free(board);
}

cell_t *board_cell(board_t *board, int row, int col) {
  return &board->cells[row * board->cols + col];
}

snake_t *create_snake(board_t *board, int row, int col, direction_t heading) {
  snake_node_t *node = (snake_node_t *)malloc(sizeof(snake_node_t));
  node->row = row, node->col = col, node->next = NULL;
  snake_t *snake = (snake_t *)malloc(sizeof(snake_t));
  snake->head = snake->tail = node, snake->heading = heading, snake->growth = 0;
  *board_cell(board, row, col) = CELL_SNAKE;
  return snake;
}

void destroy_snake(snake_t *snake) {
  snake_node_t *p = snake->head;
  while (p) {
    snake_node_t *p2 = p->next;
    free(p);
    p = p2;
  }
  free(snake);
}

void randomly_add_food(board_t *board, float probability) {
}

void set_direction(snake_t *snake, direction_t d) { snake->heading = d; }

void update_snake_head(snake_t *snake, board_t *board, int growth_per_food) {
  int d = snake->heading;
  int tx = snake->head->row + dx[d];
  int ty = snake->head->col + dy[d];
  *board_cell(board, tx, ty) = CELL_SNAKE;
  snake_node_t *node = (snake_node_t *)malloc(sizeof(snake_node_t));
  node->row = tx, node->col = ty, node->next = snake->head;
  snake->head = node;
}

void update_snake_tail(snake_t *snake, board_t *board) {
}

int invalid(game_t *game, snake_t *snake) {
  int d = snake->heading;
  int tx = snake->head->row + dx[d];
  int ty = snake->head->col + dy[d];
  if (*board_cell(game->board, tx, ty) >= 2) {
    return 1;
  }
  return 0;
}

int next_frame(game_t *game) {
  int f1 = invalid(game, game->snake1), f2 = invalid(game, game->snake2);
  if (f1 && f2) return 0;
  if (f2) return 1;
  if (f1) return 2;
  update_snake_head(game->snake1, game->board, game->growth_per_food);
  update_snake_tail(game->snake1, game->board);
  update_snake_head(game->snake2, game->board, game->growth_per_food);
  update_snake_tail(game->snake2, game->board);
  randomly_add_food(game->board, game->food_probability);
  return -1;
}
