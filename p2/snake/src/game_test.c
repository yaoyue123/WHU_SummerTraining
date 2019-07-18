#include "game.h"
#include <assert.h>
#include <stdlib.h>

void test_create_board() {
  board_t* board = create_board(5, 5);
  assert(board != NULL);
  assert(board_cell(board, 0, 0) != NULL);
  cell_t* cell = board_cell(board, 3, 2);
  assert(cell != NULL && *cell == CELL_OPEN);
  assert(board_cell(board, -1, 0) == NULL);
  assert(board_cell(board, 0, 5) == NULL);
  assert(board_cell(board, 5, 5) == NULL);
  assert(board_cell(board, 4, 4) != NULL);
  destroy_board(board);
}

int main(int argc, char** argv) {
  test_create_board();
  return 0;
}
