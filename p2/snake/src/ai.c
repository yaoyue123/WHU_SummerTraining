#include "ai.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *bfs(game_t *game, int start_x, int start_y, int end_x, int end_y, int *dist) {
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    int **visit = malloc(sizeof(int *) * game->board->rows);
    for(int i = 0; i < game->board->rows; i++) {
        visit[i] = malloc(sizeof(int) * game->board->cols);
        for(int j = 0; j < game->board->cols; j++) {
            visit[i][j] = 0;
        }
    }
    SqQueue *q = InitQueue(game->board->rows * game->board->cols);
    ElemType elem;
    elem.x = start_x;
    elem.y = start_y;
    elem.step = -1;
    elem.before = -1;
    visit[elem.x][elem.y] = 1;
    enQueue(q, elem);
    char *path = (char *)malloc(sizeof(char) * game->board->rows * game->board->cols);
    for(int i = 0; i < game->board->rows * game->board->cols; i++)
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
            if(elem.x >= 0 && elem.x < game->board->rows
            && elem.y >= 0 && elem.y < game->board->cols
            && visit[elem.x][elem.y] == 0 && (game->board->cells[elem.x * game->board->cols + elem.y] == CELL_OPEN || 
                game->board->cells[elem.x * game->board->cols + elem.y] == CELL_FOOD)) {
                visit[elem.x][elem.y] = 1;
                enQueue(q, elem);
                if(elem.x == end_x && elem.y == end_y) {
                    int i = q->rear;
                    (*dist) = q->data[i].step + 1;
                    while(q->data[i].step >= 0) {
                        path[q->data[i].step] = q->data[i].dir;
                        i = q->data[i].before;
                    }
                    for(int i = 0; i < game->board->rows; i++) {
                        free(visit[i]);
                    }
                    free(visit);
                    DestroyQueue(q);
                    return path;
                }
            }
        }
    }

    free(path);
    for(int i = 0; i < game->board->rows; i++) {
        free(visit[i]);
    }
    free(visit);
    DestroyQueue(q);
    return NULL;
}

direction_t get_action(game_t* game) {
    char *path, ch;
    int foodx = -1, foody = -1;
    int mindis = 999999999;
    for(int i = 0; i < game->board->rows; i++) {
        for(int j = 0; j < game->board->cols; j++) {
            if(game->board->cells[i * game->board->cols + j] == CELL_FOOD) {
                foodx = i;
                foody = j;
                int dis = 999999999;
                path = bfs(game, game->snake->head->row, game->snake->head->col, foodx, foody, &dis);
                if(path == NULL) {
                    continue;
                }
                if(dis < mindis) {
                    mindis = dis;
                    ch = path[0];
                }
                free(path);
            }
        }
    }
    if(mindis == 999999999) {
        int row = game->snake->head->row;
        int col = game->snake->head->col;
        if(game->board->cells[(row + 1) * game->board->cols + col] == CELL_OPEN)
            return SOUTH;
        if(game->board->cells[(row - 1) * game->board->cols + col] == CELL_OPEN)
            return NORTH;
        if(game->board->cells[row * game->board->cols + col + 1] == CELL_OPEN)
            return EAST;
        return WEST;
    }
    switch(ch) {
        case 'E':return EAST; break;
        case 'S':return SOUTH; break;
        case 'W':return WEST; break;
        case 'N':return NORTH; break;
    }
}