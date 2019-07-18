#include "ai.h"
#include <stdlib.h>
#include "queue.h"
direction_t bfs_t(game_t *game, int foodx, int foody, int *dist) 
{
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    direction_t direction[4] = {EAST, SOUTH, WEST, NORTH};
    const int INF = 999999999;

    int snake_length = 0;
    snake_node_t *ptr = game->snake->head;
    while(ptr != NULL) {
        snake_length++;
        ptr = ptr->next;
    }
    int **life = malloc(sizeof(int *) * game->board->rows);
    int **visit = malloc(sizeof(int *) * game->board->rows);
    for(int i = 0; i < game->board->rows; i++) {
        life[i] = malloc(sizeof(int) * game->board->cols);
        visit[i] = malloc(sizeof(int) * game->board->cols);
        for(int j = 0; j < game->board->cols; j++) {
            life[i][j] = 0;
            visit[i][j] = 0;
        }
    }
    for(int i = 0; i < game->board->rows; i++) {
        for(int j = 0; j < game->board->cols; j++) {
            if(game->board->cells[i * game->board->cols + j] == CELL_WALL) {
                life[i][j] = INF;
            }
        }
    }
    ptr = game->snake->head;
    int cur_life = snake_length + game->snake->growth;
    while(ptr != NULL) {
        life[ptr->row][ptr->col] = cur_life;
        cur_life--;
        ptr = ptr->next;
    }
    SqQueue *q = InitQueue(game->board->rows * game->board->cols);
    ElemType elem;
    elem.x = game->snake->head->row;
    elem.y = game->snake->head->col;
    elem.step = 0;
    elem.direction = game->snake->heading;
    elem.before = -1;
    enQueue(q, elem);
    visit[elem.x][elem.y] = 1;
    while(!QueueEmpty(q)) {
        ElemType temp;
        deQueue(q, &temp);
        for(int i = 0; i < 4; i++) {
            ElemType e;
            e.x = temp.x + dirx[i];
            e.y = temp.y + diry[i];
            e.step = temp.step + 1;
            e.direction = direction[i];
            e.before = q->front;
            if(e.step >= life[e.x][e.y] && abs((int)e.direction - (int)temp.direction) != 2 && visit[e.x][e.y] == 0) {
                enQueue(q, e);
                visit[e.x][e.y] = 1;
                if(e.x == foodx && e.y == foody) {
                    int i = q->rear;
                    direction_t dir;
                    while(q->data[i].before != 0) {
                        i = q->data[i].before;
                    }
                    dir = q->data[i].direction;
                    DestroyQueue(q);
                    for(int i = 0; i < game->board->rows; i++) {
                        free(life[i]);
                        free(visit[i]);
                    }
                    free(life);
                    free(visit);
                    (*dist) = e.step;
                    return dir;
                }
            }
        }
    }
    DestroyQueue(q);
    for(int i = 0; i < game->board->rows; i++) {
        free(life[i]);
        free(visit[i]);
    }
    free(life);
    free(visit);
    (*dist) = -1;
    return EAST;
}

direction_t get_action(game_t* game) 
{
    int mindist = 999999999;
    direction_t best_dir;
    for(int i = 0; i < game->board->rows; i++) {
        for(int j = 0; j < game->board->cols; j++) {
            if(game->board->cells[i * game->board->cols + j] == CELL_FOOD) {
                int dist;
                direction_t dir = bfs_t(game, i, j, &dist);
                if(dist == -1) {
                    continue;
                }
                if(mindist > dist) {
                    mindist = dist;
                    best_dir = dir;
                }
            }
        }
    }

    if(mindist == 999999999) {
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
    return best_dir;
}