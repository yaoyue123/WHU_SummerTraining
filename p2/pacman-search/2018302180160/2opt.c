#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

typedef struct {
    int x;
    int y;
} Point;

void greedy(game_state_t state, int **location, int *order) {
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    int **vis = malloc(sizeof(int *) * state.n);
    for(int i = 0; i < state.n; i++) {
      vis[i] = malloc(sizeof(int) * state.m);
      for(int j = 0; j < state.m; j++) {
          vis[i][j] = 0;
      }
    }
    SqQueue *q = InitQueue(state.n * state.m);
    ElemType elem;
    elem.x = state.start_x;
    elem.y = state.start_y;
    elem.step = -1;
    elem.before = -1;
    vis[elem.x][elem.y] = 1;
    enQueue(q, elem);
    char *path = (char *)malloc(sizeof(char) * state.n * state.m);
    for(int i = 0; i < state.n * state.m; i++)
        path[i] = 0;
    int ppoint = 0;
    while(!QueueEmpty(q)) {
        ElemType temp;
        deQueue(q, &temp);
        for(int i = 0; i < 4; i++) {
            ElemType elem;
            elem.x = temp.x + dirx[i];
            elem.y = temp.y + diry[i];
            elem.step = temp.step + 1;
            elem.dir = dir[i];
            elem.before = q->front;
            if(elem.x >= 0 && elem.x < state.n
            && elem.y >= 0 && elem.y < state.m
            && vis[elem.x][elem.y] == 0 && state.grid[elem.x][elem.y] == 0) {
                vis[elem.x][elem.y] = 1;
                enQueue(q, elem);
                if(state.food[elem.x][elem.y] == 1) {
                    order[ppoint] = location[elem.x][elem.y];
                    ppoint++;
                    DestroyQueue(q);
                    q = InitQueue(state.m * state.n);
                    elem.step = -1;
                    elem.before = -1;
                    state.food[elem.x][elem.y] = 0;
                    enQueue(q, elem);
                    for(int i = 0; i < state.n; i++) {
                        for(int j = 0; j < state.m; j++) {
                            vis[i][j] = 0;
                        }
                    }
                    vis[elem.x][elem.y] = 1;
                    break;
                }
            }
        }
    }
    free(path);
    for(int i = 0; i < state.n; i++) {
        free(vis[i]);
    }
    free(vis);
    DestroyQueue(q);
}

char *bfs(game_state_t state, int start_x, int start_y, int end_x, int end_y, int *dist, int **location, int *bvis) {
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    int **vis = malloc(sizeof(int *) * state.n);
    for(int i = 0; i < state.n; i++) {
        vis[i] = malloc(sizeof(int) * state.m);
        for(int j = 0; j < state.m; j++) {
            vis[i][j] = 0;
        }
    }
    SqQueue *q = InitQueue(state.n * state.m);
    ElemType elem;
    elem.x = start_x;
    elem.y = start_y;
    elem.step = -1;
    elem.before = -1;
    vis[elem.x][elem.y] = 1;
    enQueue(q, elem);
    char *path = (char *)malloc(sizeof(char) * state.n * state.m);
    for(int i = 0; i < state.n * state.m; i++)
        path[i] = 0;
    while(!QueueEmpty(q)) {
        ElemType temp;
        deQueue(q, &temp);
        for(int i = 0; i < 4; i++) {
            ElemType elem;
            elem.x = temp.x + dirx[i];
            elem.y = temp.y + diry[i];
            elem.step = temp.step + 1;
            elem.dir = dir[i];
            elem.before = q->front;
            if(elem.x >= 0 && elem.x < state.n
            && elem.y >= 0 && elem.y < state.m
            && vis[elem.x][elem.y] == 0 && state.grid[elem.x][elem.y] == 0) {
                vis[elem.x][elem.y] = 1;
                enQueue(q, elem);
                if(elem.x == end_x && elem.y == end_y) {
                    int i = q->rear;
                    (*dist) = q->data[i].step + 1;
                    while(q->data[i].step >= 0) {

                        if(state.grid[q->data[i].x][q->data[i].y] == 1) {
                            bvis[location[q->data[i].x][q->data[i].y]] = 1;
                        }

                        path[q->data[i].step] = q->data[i].dir;
                        i = q->data[i].before;
                    }
                    for(int i = 0; i < state.n; i++) {
                        free(vis[i]);
                    }
                    free(vis);
                    DestroyQueue(q);
                    return path;
                }
            }
        }
    }

    free(path);
    for(int i = 0; i < state.n; i++) {
        free(vis[i]);
    }
    free(vis);
    DestroyQueue(q);
    return NULL;
}

int main() {
    game_state_t state;
    memset(&state, 0, sizeof(state));
    init(&state);
    // write your code here
    srand(time(NULL));
    Point *douzi;
    int num_douzi = 0;
    int **location = malloc(sizeof(int *) * state.n);
    for(int i = 0; i < state.n; i++) {
        location[i] = malloc(sizeof(int) * state.m);
        for(int j = 0; j < state.m; j++) {
            location[i][j] = -1;
        }
    }
    douzi = (Point *)malloc(sizeof(Point) * state.n * state.m);
    for(int i = 0; i < state.n; i++) {
        for(int j = 0; j < state.m; j++) {
            if(state.food[i][j] == 1) {
                douzi[num_douzi].x = i;
                douzi[num_douzi].y = j;
                location[i][j] = num_douzi;
                num_douzi++;
            }
        }
    }
    int *start_list = malloc(sizeof(int) * num_douzi);
    int **dis_list = malloc(sizeof(int *) * num_douzi);
    for(int i = 0; i < num_douzi; i++) {
        start_list[i] = -1;
        dis_list[i] = malloc(sizeof(int) * num_douzi);
        for(int j = 0; j < num_douzi; j++) {
            dis_list[i][j] = -1;
        }
    }
    int *order = (int *)malloc(sizeof(int) * (num_douzi + 5));
    greedy(state, location, order);
    int *vis = (int *)malloc(sizeof(int) * (num_douzi + 5));
    memset(vis, 0, sizeof(int) * num_douzi);
    int dist;
    int distmin = 0;
    char *path = bfs(state, state.start_x, state.start_y, douzi[order[0]].x, douzi[order[0]].y, &dist, location, vis);
    distmin += dist;
    free(path);
    start_list[order[0]] = dist;
    for(int i = 1; i < num_douzi; i++) {
        int k = i;
        while(k < num_douzi) {
            if(vis[order[k]] == 1)
                k++;
            else
                break;
        }
        if(k == num_douzi)
            break;
        path = bfs(state, douzi[order[i - 1]].x, douzi[order[i - 1]].y, douzi[order[k]].x, douzi[order[k]].y, &dist, location, vis);
        free(path);
        distmin += dist;
        dis_list[order[i - 1]][order[k]] = dis_list[order[k]][order[i - 1]] = dist;
    }
    for(register int i = 0; i < 1000000; i++) {
        int startPoint = rand() % num_douzi;
        int endPoint = rand() % num_douzi;
        if(startPoint >= endPoint) {
            i--;
            continue;
        }
        int *neworder = (int *)malloc(sizeof(int) * num_douzi);
        for(int i = 0; i < startPoint; i++) {
            neworder[i] = order[i];
        }
        for(int i = startPoint; i <= endPoint; i++) {
            neworder[i] = order[startPoint + endPoint - i];
        }
        for(int i = endPoint + 1; i < num_douzi; i++) {
            neworder[i] = order[i];
        }
        int dist;
        int distsum = 0;
        memset(vis, 0, sizeof(int) * num_douzi);
        if(start_list[neworder[0]] != -1) {
            distsum += start_list[neworder[0]];
        } else {
            path = bfs(state, state.start_x, state.start_y, douzi[neworder[0]].x, douzi[neworder[0]].y, &dist, location, vis);
            free(path);
            distsum += dist;
            start_list[neworder[0]] = dist;
        }
        for(int i = 1; i < num_douzi; i++) {
            int k = i;
            while(k < num_douzi) {
                if(vis[order[k]] == 1)
                    k++;
                else
                    break;
            }
            if(k == num_douzi)
                break;
            if(dis_list[neworder[i - 1]][neworder[k]] != -1)
                distsum += dis_list[neworder[i - 1]][neworder[k]];
            else {
                path = bfs(state, douzi[neworder[i - 1]].x, douzi[neworder[i - 1]].y, douzi[neworder[k]].x, douzi[neworder[k]].y, &dist, location, vis);
                free(path);
                distsum += dist;
                dis_list[neworder[i - 1]][neworder[k]] = dis_list[neworder[k]][neworder[i - 1]] = dist;
            }
        }
        if(distsum < distmin) {
            distmin = distsum;
            memcpy(order, neworder, sizeof(int) * num_douzi);
        }
        free(neworder);
    }
    memset(vis, 0, sizeof(int) * num_douzi);
    path = bfs(state, state.start_x, state.start_y, douzi[order[0]].x, douzi[order[0]].y, &dist, location, vis);
    printf("%s", path);
    free(path);
    for(int i = 1; i < num_douzi; i++) {
        int k = i;
        while(k < num_douzi) {
            if(vis[order[k]] == 1)
                k++;
            else
                break;
        }
        if(k == num_douzi)
            break;
        path = bfs(state, douzi[order[i - 1]].x, douzi[order[i - 1]].y, douzi[order[k]].x, douzi[order[k]].y, &dist, location, vis);
        printf("%s", path);
        free(path);
    }
    free(douzi);
    free(order);
    for(int i = 0; i < state.n; i++) {
        free(location[i]);
    }
    free(location);
    for(int i = 0; i < num_douzi; i++) {
        free(dis_list[i]);
    }
    free(dis_list);
    free(start_list);
    free(vis);
    //
    destroy(&state);
    return 0;
}
