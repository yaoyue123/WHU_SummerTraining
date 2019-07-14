#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
  srand(time(0));
  int dx[] = {-1, 0, 0, 1};
  int dy[] = {0, -1, 1, 0};
  char d_name[] = {NORTH, WEST, EAST, SOUTH};
  while (1) {
    int d = rand() % 4;
    int sx = (state.is_red ? state.red_x : state.blue_x);
    int sy = (state.is_red ? state.red_y : state.blue_y);
    int tx = sx + dx[d];
    int ty = sy + dy[d];
    if (tx >= 0 && tx < state.n && ty >= 0 && ty < state.m &&
        !state.grid[tx][ty]) {
      putchar(d_name[d]);
      break;
    }
  }
  //
  destroy(&state);
  return 0;
}
