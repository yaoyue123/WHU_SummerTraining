#ifndef UTIL_H_
#define UTIL_H_

#define NORTH 'N'
#define SOUTH 'S'
#define WEST 'W'
#define EAST 'E'

typedef struct {
  int n, m;    // 地图的长宽
  int **grid;  // n*m的01数组，1表示墙
  double **cost;  // n*m，每个点的权重
  int start_x, start_y;
  int goal_x, goal_y; // 起点位置，终点位置
} game_state_t;

// init state from stdin, exec only once
void init(game_state_t *);

// free memory
void destroy(game_state_t *);

#endif // UTIL_H_
