#ifndef UTIL_H_
#define UTIL_H_

#define NORTH 'N'
#define SOUTH 'S'
#define WEST 'W'
#define EAST 'E'

typedef struct {
  int n, m;    // 地图的长宽
  int **grid;  // n*m的01数组，1表示墙
  int **food;  // n*m的01数组，1表示这个位置有食物
  int red_x, red_y;  // 红方pacman坐标
  int blue_x, blue_y;  // 蓝方pacman坐标
  int is_red;      // 当前是否是红队
  int num_ghosts; // ghost数量
  int *ghost_x, *ghost_y; // ghost坐标
} game_state_t;

// init state from stdin, exec only once
void init(game_state_t *);

// free memory
void destroy(game_state_t *);

#endif // UTIL_H_
