#include "util.h"
#include <stdio.h>
#include <string.h>
#define INF 100000000
#define M 1000

int pre[M][M], dis[M][M], used[M][M];
int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};
char d_name[] = {'N', 'W', 'E', 'S'};

void bfs(game_state_t *state, int sx, int sy) {
  	static int qx[200000], qy[200000], head = 0, tail = 0;
  	head = tail = 0;
  	memset(dis, -1, sizeof(dis));
  	dis[sx][sy] = 1;
  	pre[sx][sy] = -1;
  	qx[head] = sx, qy[head] = sy, head++;
 	while (tail < head) {
    	int x = qx[tail], y = qy[tail];
    	tail++;
    	int i, tx, ty;
    	for (i = 0; i < 4; i++) {
      		tx = x + dx[i];
      		ty = y + dy[i];
      		if (tx >= 0 && tx < state->n && ty >= 0 && ty < state->m && state->grid[tx][ty] == 0) {
        		if (dis[tx][ty] == -1) {
          			dis[tx][ty] = dis[x][y] + 1;
          			pre[tx][ty] = i;
          			qx[head] = tx, qy[head] = ty, head++;
        		}
      		}
    	}
  	}
}

int main() {
  	game_state_t state;
  	memset(&state, 0, sizeof(state));
  	init(&state);
  	int path[M * 10], top = 0;
  	int nx = state.start_x, ny = state.start_y;
  	while (1) {
    	bfs(&state, nx, ny);
    	int mx = INF, zx = 0, zy = 0;
    	for (int i = 0; i < state.n; i++) {
    		for (int j = 0; j < state.m; j++) {
        		if (state.food[i][j] == 1 && dis[i][j] < mx) {
        			mx = dis[i][j], zx = i, zy = j;
        		}
      		}
    	}
    	if (mx == INF) {
    		break;
		}
    	state.food[zx][zy] = 0;
    	int x = zx, y = zy;
    	top = 0;
    	while (x != nx || y != ny) {
      		int d = pre[x][y];
      		path[top++] = d;
      		x -= dx[d], y -= dy[d];
    	}
    	while (--top >= 0) {
      		printf("%c", d_name[path[top]]);
    	}
    	nx = zx, ny = zy;
  	}
  	destroy(&state);
  	return 0;
}
