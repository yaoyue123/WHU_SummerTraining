#include "ai.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const static int dx[] = {0, 1, 0, -1};
const static int dy[] = {1, 0, -1, 0};
#define N 100
#define M 100000

void bfs(int sx, int sy, game_t* game, int dis[][N]) {
  static int qx[M], qy[M];
  int head = 0, tail = 0;
  memset(dis, 0x3f3f3f3f, sizeof(int) * N * N);
  dis[sx][sy] = 0;
  qx[head] = sx, qy[head] = sy, head++;
  while (tail < head) {
    int x = qx[tail], y = qy[tail];
    tail++;
    for (int i = 0; i < 4; i++) {
      int tx = x + dx[i], ty = y + dy[i];
      if (*board_cell(game->board, tx, ty) == CELL_OPEN &&
          dis[tx][ty] > dis[x][y] + 1) {
        dis[tx][ty] = dis[x][y] + 1;
        qx[head] = tx, qy[head] = ty, head++;
      }
    }
  }
}

int eval(game_t* game, int sx, int sy, snake_t* snake2) {
  int dis1[N][N], dis2[N][N];
  bfs(sx, sy, game, dis1);
  bfs(snake2->head->row, snake2->head->col, game, dis2);
  int cnt1 = 0, cnt2 = 0;
  for (int i = 0; i < game->board->rows; i++) {
    for (int j = 0; j < game->board->cols; j++) {
      cnt1 += dis1[i][j] < dis2[i][j];
      cnt2 += dis2[i][j] < dis1[i][j];
    }
  }
  return cnt1 - cnt2 + 10000;
}

direction_t simple(game_t *game, snake_t *snake1, snake_t *snake2) {
  int x = snake1->head->row, y = snake1->head->col;
  direction_t cand[10];
  int pd = 0;
  int mx_score = 0;
  for (int i = 0; i < 4; i++) {
    int tx = x + dx[i], ty = y + dy[i];
    if (*board_cell(game->board, tx, ty) == CELL_OPEN) {
      int score = eval(game, tx, ty, snake2);
      if (score > mx_score) {
        mx_score = score;
        cand[0] = i;
        pd = 1;
      } else if (score == mx_score) {
        cand[pd++] = i;
      }
    }
  }
  if (pd == 0) return NORTH;
  return cand[rand() % pd];
}

direction_t rand_action(game_t *game, snake_t *snake) {
  int x = snake->head->row;
  int y = snake->head->col;
  for (int i = 0; i < 10000; i++) {
    int d = rand() % 4;
    int tx = x + dx[d], ty = y + dy[d];
    if (*board_cell(game->board, tx, ty) < 2) {
      return (direction_t)d;
    }
  }
  return NORTH;
}

direction_t get_action1(game_t *game) {
  return simple(game, game->snake1, game->snake2);
  //  return rand_action(game, game->snake1);
}

