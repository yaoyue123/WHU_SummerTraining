#include <stdio.h>
#include "queue.h"

int n, m; 
char mp[20][20];
int vis[20][20];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
queue q;

int bfs(int x, int y) {
    init(&q);
    node tmp = {x, y, 0};
    vis[x][y] = 1;
    push(&q, tmp);
    while (size(&q)) {
        tmp = pop(&q);
        x = tmp.x;
        y = tmp.y;
        int step = tmp.step;
        if (mp[x][y] == 'T') {
            return step;
        }
        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            node temp = {tx, ty, step + 1};
            if (tx >= 0 && tx < n &&
                ty >= 0 && ty < m &&
                mp[tx][ty] != '*' &&
                vis[tx][ty] == 0) {
                vis[tx][ty] = 1;
                push(&q, temp);
            }
        }

    }
    return -1;
}


int main() {
    int x, y;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", mp[i]);
        for (int j = 0; j < m; j++) {
            if (mp[i][j] == 'S') {
                x = i;
                y = j;
            }
        }
    }
    printf("%d\n", bfs(x, y));
    return 0;
}
