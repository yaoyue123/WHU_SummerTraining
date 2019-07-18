#include <stdlib.h>
#include <stdio.h>
#include "ai.h"
#include "game.h"
#include "queue.h"

direction_t bfs(game_t *game, int **sec, int startx, int starty, int endx, int endy, int *dist, direction_t *initDir) {
    if(startx == endx && starty == endy) {
        (*dist) = 0;
        return EAST;
    }
    int dx[4] = { 0, 1, 0,-1};
    int dy[4] = { 1, 0,-1, 0};
    direction_t direction[4] = {EAST, SOUTH, WEST, NORTH};
    const int INF = 1111111111;

    int **visit = malloc(sizeof(int *) * game->board->rows);
    for(int i = 0; i < game->board->rows; i++) {
        visit[i] = malloc(sizeof(int) * game->board->cols);
        for(int j = 0; j < game->board->cols; j++) {
            visit[i][j] = 0;
        }
    }

    SqQueue *q = InitQueue(game->board->rows * game->board->cols);
    ElemType elem;
    elem.x = startx;
    elem.y = starty;
    elem.step = 0;
    elem.direction = (*initDir);
    elem.before = -1;
    enQueue(q, elem);
    visit[elem.x][elem.y] = 1;
    int sec_base = sec[startx][starty];

    while(!QueueEmpty(q)) {
        ElemType temp;
        deQueue(q, &temp);
        for(int i = 0; i < 4; i++) {
            ElemType e;
            e.x = temp.x + dx[i];
            e.y = temp.y + dy[i];
            e.step = temp.step + 1;
            e.direction = direction[i];
            e.before = q->front;
            if(e.step >= sec[e.x][e.y] && abs((int)e.direction - (int)temp.direction) != 2 && visit[e.x][e.y] == 0) {
                enQueue(q, e);
                visit[e.x][e.y] = 1;
                if(e.x == endx && e.y == endy) {
                    (*initDir) = e.direction;
                    int i = q->rear;
                    while(q->data[i].before != 0) {
                        sec[q->data[i].x][q->data[i].y] = sec_base + q->data[i].step;
                        i = q->data[i].before;
                    }
                    sec[q->data[i].x][q->data[i].y] = sec_base + q->data[i].step;
                    direction_t dir = q->data[i].direction;
                    for(int i = 0; i < game->board->rows; i++) {
                        for(int j = 0; j < game->board->cols; j++) {
                            sec[i][j] = (sec[i][j] - e.step > 0) ? (sec[i][j] - e.step) : 0;
                            sec[i][j] = (sec[i][j] == 0) ? 0 : (sec[i][j] + game->growth_per_food);
                        }
                    }
                    DestroyQueue(q);
                    for(int i = 0; i < game->board->rows; i++) {
                        free(visit[i]);
                    }
                    free(visit);
                    (*dist) = e.step;
                    return dir;
                }
            }
        }
    }
    DestroyQueue(q);
    for(int i = 0; i < game->board->rows; i++) {
        free(visit[i]);
    }
    free(visit);
    (*dist) = -1;
    return EAST;
}

int **InitLife(game_t *game) {
    const int INF = 1111111111;

    int snake_length = 0;
    snake_node_t *ptr = game->snake->head;
    while(ptr != NULL) {
        snake_length++;
        ptr = ptr->next;
    } 
    int **sec = malloc(sizeof(int *) * game->board->rows);
    for(int i = 0; i < game->board->rows; i++) {
        sec[i] = malloc(sizeof(int) * game->board->cols);
        for(int j = 0; j < game->board->cols; j++)
        sec[i][j] = 0;
    }
    for(int i = 0; i < game->board->rows; i++)
        for(int j = 0; j < game->board->cols; j++)
            if(game->board->cells[i * game->board->cols + j] == CELL_WALL)
            sec[i][j] = INF;
    ptr = game->snake->head;
    int cur_sec = snake_length + game->snake->growth;
    while(ptr != NULL) {
        sec[ptr->row][ptr->col] = cur_sec;
        cur_sec--;
        ptr = ptr->next;
    }
    return sec;
}

void DestroyLife(game_t *game, int **sec) {
    for(int i = 0; i < game->board->rows; i++)
        free(sec[i]);
    free(sec);
}

direction_t get_action(game_t* game)
{
    int mindist = 1111111111;
    direction_t best_dir;
    for(int i = 0; i < game->board->rows; i++) {
        for(int j = 0; j < game->board->cols; j++) {
            if(game->board->cells[i * game->board->cols + j] == CELL_FOOD) {
                int **sec;
                int dist;
                direction_t initDir = game->snake->heading;
                sec = InitLife(game);
                direction_t dir = bfs(game, sec, game->snake->head->row, game->snake->head->col, i, j, &dist, &initDir);
                if(dist == -1) {
                    DestroyLife(game, sec);
                    continue;
                }
                int tail_x = -1, tail_y;
                int lowest_sec = 1111111111;
                for(int i = 0; i < game->board->rows; i++) {
                    for(int j = 0; j < game->board->cols; j++) {
                        if(sec[i][j] < lowest_sec && sec[i][j] > 0) {
                            lowest_sec = sec[i][j];
                            tail_x = i;
                            tail_y = j;
                        }
                    }
                }
                int dist2;
                bfs(game, sec, i, j, tail_x, tail_y, &dist2, &initDir);
                if(dist2 == -1) {
                    DestroyLife(game, sec);
                    continue;
                }
                DestroyLife(game, sec);
                if(mindist > dist) {
                    mindist = dist;
                    best_dir = dir;
                }
            }
        }
    }
    if(mindist == 1111111111) {
        int dist;
        direction_t initDir = game->snake->heading;
        int **sec;
        sec = InitLife(game);
        best_dir = bfs(game, sec, game->snake->head->row, game->snake->head->col, game->snake->tail->row, game->snake->tail->col, &dist, &initDir);
        DestroyLife(game, sec);
        if(dist != -1 && game->snake->head != game->snake->tail)
            return best_dir;

        int row = game->snake->head->row;
        int col = game->snake->head->col;
        if(game->board->cells[(row + 1) * game->board->cols + col] == CELL_OPEN && game->snake->heading != NORTH)
            return SOUTH;
        if(game->board->cells[(row - 1) * game->board->cols + col] == CELL_OPEN && game->snake->heading != SOUTH)
            return NORTH;
        if(game->board->cells[row * game->board->cols + col + 1] == CELL_OPEN && game->snake->heading != WEST)
            return EAST;
        return WEST;
    }
    return best_dir;
}
