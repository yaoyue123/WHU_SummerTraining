#include "util.h"
#include <stdio.h>
#include <string.h>
#include "bits/stdc++.h"


void build(game_state_t *state, graph *g) {
  for (int i = 0; i < state->n; i++) {
      for (int j = 0; j < state->m; j++) {
          for (int k = 0; k < 4; k++) {
              int x = i + dx[k];
              int y = j + dy[k];
              if (x > 0 && x < state->n - 1 && y > 0 && y < state->m - 1 && state->grid[x][y] == 0) {
                    add(g, i * state->m + j, x * state->m + y, 1, dr[k], state->food[x][y]);
                    //printf("%d %d\n", i * state->m + j, x * state->m + y, 1);
              }
          }
      }
  }
  //printf("%d\n", g->eid);
}

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  int nx = (state.is_red ? state.red_x : state.blue_x);
  int ny = (state.is_red ? state.red_y : state.blue_y);
  // write your code here
    int bak[state.n + 10][state.m + 10];
    memset(bak, 0, sizeof bak);
    for (int k = 0; k < state.num_ghosts; k++) {
        int x = state.ghost_x[k];
        int y = state.ghost_y[k];
        bak[x][y] = 100;
        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx == nx && ty == ny) continue;
            bak[tx][ty] = state.grid[tx][ty];
            state.grid[tx][ty] = 1;
        }
    }

  graph g;
  graph_init(&g, state.n * state.m * 4, state.n * state.m);
  build(&state, &g);

  result res = bfs(&g, nx * state.m + ny, 1);
  //printf("*********%d\n", res.pos);
  if (res.pos != -1)  {
    print(res.fa, res.dir, res.pos);
    return 0;
}

  graph_init(&g, state.n * state.m * 4, state.n * state.m);
  build(&state, &g);
    for (int k = 0; k < state.num_ghosts; k++) {
        int x = state.ghost_x[k];
        int y = state.ghost_y[k];
        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            state.grid[tx][ty] = bak[tx][ty];
        }
    }
  res = bfs(&g, nx * state.m + ny, 1);
    print(res.fa, res.dir, res.pos);

  graph_free(&g);
  result_free(&res);

  //
  destroy(&state);
  return 0;
}
