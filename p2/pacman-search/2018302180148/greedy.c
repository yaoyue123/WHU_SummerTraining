#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
  
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    int **visit = malloc(sizeof(int *) * state.n);
    for(int i = 0; i < state.n; i++) {
      visit[i] = malloc(sizeof(int) * state.m);
      for(int j = 0; j < state.m; j++) {
          visit[i][j] = 0;
      }
    }
    SqQueue *q = InitQueue(state.n * state.m);
    ElemType elem;
    elem.x = state.start_x;
    elem.y = state.start_y;
    elem.step = -1;
    elem.before = -1;
    visit[elem.x][elem.y] = 1;
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
            && visit[elem.x][elem.y] == 0 && state.grid[elem.x][elem.y] == 0) {
                visit[elem.x][elem.y] = 1;
                enQueue(q, elem);
                if(state.food[elem.x][elem.y] == 1) {
                    int i = q->rear;
                    while(q->data[i].step >= 0) {
                        path[q->data[i].step] = q->data[i].dir;
                        i = q->data[i].before;
                    }
                    printf("%s", path);
                    for(int i = 0; i < state.n * state.m; i++)
                        path[i] = 0;
                    DestroyQueue(q);
                    q = InitQueue(state.m * state.n);
                    elem.step = -1;
                    elem.before = -1;
                    state.food[elem.x][elem.y] = 0;
                    enQueue(q, elem);
                    for(int i = 0; i < state.n; i++) {
                        for(int j = 0; j < state.m; j++) {
                            visit[i][j] = 0;
                        }
                    }
                    visit[elem.x][elem.y] = 1;
                    break;
                }
            }
        }
    }

    free(path);
    for(int i = 0; i < state.n; i++) {
        free(visit[i]);
    }
    free(visit);
    DestroyQueue(q);
  // 
  destroy(&state);
  return 0;
}
