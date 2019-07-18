#include "ai.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
const static int dx[] = {0,1,0,-1};
const static int dy[] = {1,0,-1,0};

char *bfs(game_t *game, int start_x, int start_y, int end_x, int end_y, int *dist)
{
    int dirx[4] = {0, 1, 0, -1};
    int diry[4] = {1, 0, -1, 0};
    char dir[4] = {'E', 'S', 'W', 'N'};
    int **visit = malloc(sizeof(int *) * game->board->rows);
    for (int i = 0; i < game->board->rows; i++)
    {
        visit[i] = malloc(sizeof(int) * game->board->cols);
        for (int j = 0; j < game->board->cols; j++)
        {
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
    for (int i = 0; i < game->board->rows * game->board->cols; i++)
        path[i] = 0;
    while (!QueueEmpty(q))
    {
        ElemType temp;
        deQueue(q, &temp);
        for (int i = 0; i < 4; i++)
        {
            ElemType elem;
            elem.x = temp.x + dirx[i];
            elem.y = temp.y + diry[i];
            elem.step = temp.step + 1;
            elem.dir = dir[i];
            elem.before = q->front;
            if (elem.x >= 0 && elem.x < game->board->rows && elem.y >= 0 && elem.y < game->board->cols && visit[elem.x][elem.y] == 0 && (game->board->cells[elem.x * game->board->cols + elem.y] == CELL_OPEN || game->board->cells[elem.x * game->board->cols + elem.y] == CELL_FOOD))
            {
                visit[elem.x][elem.y] = 1;
                enQueue(q, elem);
                if (elem.x == end_x && elem.y == end_y)
                {
                    int i = q->rear;
                    (*dist) = q->data[i].step + 1;
                    while (q->data[i].step >= 0)
                    {
                        path[q->data[i].step] = q->data[i].dir;
                        i = q->data[i].before;
                    }
                    for (int i = 0; i < game->board->rows; i++)
                    {
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
    for (int i = 0; i < game->board->rows; i++)
    {
        free(visit[i]);
    }
    free(visit);
    DestroyQueue(q);
    return NULL;
}

direction_t bfs_tail(game_t *game, int **life, int startx, int starty, int endx, int endy, int *dist, direction_t *initDir) {
    if(startx == endx && starty == endy) {
        (*dist) = 0;
        return EAST;
    }
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    direction_t direction[4] = {EAST, SOUTH, WEST, NORTH};
    const int INF = 999999999;

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
    int life_base = life[startx][starty];

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
            if(e.step > life[e.x][e.y] && abs((int)e.direction - (int)temp.direction) != 2 && visit[e.x][e.y] == 0) {
                enQueue(q, e);
                visit[e.x][e.y] = 1;
                if(e.x == endx && e.y == endy) {
                    (*initDir) = e.direction;
                    int i = q->rear;
                    while(q->data[i].before != 0) {
                        life[q->data[i].x][q->data[i].y] = life_base + q->data[i].step;
                        i = q->data[i].before;
                    }
                    life[q->data[i].x][q->data[i].y] = life_base + q->data[i].step;
                    direction_t dir = q->data[i].direction;
                    for(int i = 0; i < game->board->rows; i++) {
                        for(int j = 0; j < game->board->cols; j++) {
                            life[i][j] = (life[i][j] - e.step > 0) ? (life[i][j] - e.step) : 0;
                            life[i][j] = (life[i][j] == 0) ? 0 : (life[i][j] + game->growth_per_food);
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
    const int INF = 999999999;

    int snake_length1 = 0;
    int snake_length2 = 0;
    snake_node_t *ptr = game->snake1->head;
    while(ptr != NULL) {
        snake_length1++;
        ptr = ptr->next;
    }

    ptr = game->snake2->head;
    while(ptr != NULL) {
        snake_length2++;
        ptr = ptr->next;
    }

    int **life = malloc(sizeof(int *) * game->board->rows);
    for(int i = 0; i < game->board->rows; i++) {
        life[i] = malloc(sizeof(int) * game->board->cols);
        for(int j = 0; j < game->board->cols; j++) {
            life[i][j] = 0;
        }
    }
    for(int i = 0; i < game->board->rows; i++) {
        for(int j = 0; j < game->board->cols; j++) {
            if(game->board->cells[i * game->board->cols + j] == CELL_WALL) {
                life[i][j] = INF;
            }
        }
    }
    ptr = game->snake1->head;
    int cur_life = snake_length1 + game->snake1->growth;
    while(ptr != NULL) {
        life[ptr->row][ptr->col] = cur_life;
        cur_life--;
        ptr = ptr->next;
    }
    ptr = game->snake2->head;
    cur_life = snake_length2 + game->snake2->growth;
    while(ptr != NULL) {
        life[ptr->row][ptr->col] = cur_life;
        cur_life--;
        ptr = ptr->next;
    }

    return life;
}

void DestroyLife(game_t *game, int **life) {
    for(int i = 0; i < game->board->rows; i++) {
        free(life[i]);
    }
    free(life);
}

direction_t get_action1(game_t *game)
{
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};

    int snake_length = 0;
    snake_node_t *ptr = game->snake1->head;
    while(ptr != NULL) {
        snake_length++;
        ptr = ptr->next;
    }
    if(snake_length > game->board->rows * 2 + game->board->cols * 2) {
        int index;
        switch(game->snake2->heading) {
            case NORTH:
                index = 3;
                break;
            case SOUTH:
                index = 1;
                break;
            case EAST:
                index = 0;
                break;
            case WEST:
                index = 2;
                break;
        }
        for(int i = 0; i < 4; i++, index = (index + 1) % 4) {
            int endx = game->snake2->head->row + dirx[index];
            int endy = game->snake2->head->col + diry[index];
            if(game->board->cells[endx * game->board->cols + endy] != CELL_WALL && 
            game->board->cells[endx * game->board->cols + endy] != CELL_SNAKE) {
                int **life;
                int dist;
                direction_t initDir = game->snake1->heading;
                life = InitLife(game);
                direction_t dir = bfs_tail(game, life, game->snake1->head->row, game->snake1->head->col, endx, endy, &dist, &initDir);
                if(dist == -1) {
                    DestroyLife(game, life);
                    continue;
                }
                int tail_x = -1, tail_y;
                int lowest_life = 999999999;
                for(int i = 0; i < game->board->rows; i++) {
                    for(int j = 0; j < game->board->cols; j++) {
                        if(life[i][j] < lowest_life && life[i][j] > 0) {
                            lowest_life = life[i][j];
                            tail_x = i;
                            tail_y = j;
                        }
                    }
                }
                for(int i = 0; i < 4; i++) {
                    int ax = game->snake2->head->row + dirx[i];
                    int ay = game->snake2->head->col + diry[i];
                    life[ax][ay] = 99999999;
                }
                int nextx = game->snake1->head->row;
                int nexty = game->snake1->head->col;
                switch(dir) {
                    case NORTH:
                        nextx--;break;
                    case SOUTH:
                        nextx++;break;
                    case WEST:
                        nexty--;break;
                    case EAST:
                        nexty++;break;
                }
                int dist2;
                bfs_tail(game, life, nextx, nexty, tail_x, tail_y, &dist2, &initDir);
                DestroyLife(game, life);
                if(dist2 == -1) {
                    continue;
                }
                return dir;
            }
        }
    }

    int mindist = 999999999;
    direction_t best_dir;
    for(int i = 0; i < game->board->rows; i++) {
        for(int j = 0; j < game->board->cols; j++) {
            if(game->board->cells[i * game->board->cols + j] == CELL_FOOD) {
                int **life;
                int dist;
                direction_t initDir = game->snake1->heading;
                life = InitLife(game);
                direction_t dir = bfs_tail(game, life, game->snake1->head->row, game->snake1->head->col, i, j, &dist, &initDir);
                if(dist == -1) {
                    DestroyLife(game, life);
                    continue;
                }
                int tail_x = -1, tail_y;
                int lowest_life = 999999999;
                for(int i = 0; i < game->board->rows; i++) {
                    for(int j = 0; j < game->board->cols; j++) {
                        if(life[i][j] < lowest_life && life[i][j] > 0) {
                            lowest_life = life[i][j];
                            tail_x = i;
                            tail_y = j;
                        }
                    }
                }
                for(int i = 0; i < 4; i++) {
                    int ax = game->snake2->head->row + dirx[i];
                    int ay = game->snake2->head->col + diry[i];
                    life[ax][ay] = 99999999;
                }
                int nextx = game->snake1->head->row;
                int nexty = game->snake1->head->col;
                switch(dir) {
                    case NORTH:
                        nextx--;break;
                    case SOUTH:
                        nextx++;break;
                    case WEST:
                        nexty--;break;
                    case EAST:
                        nexty++;break;
                }
                int dist2;
                bfs_tail(game, life, nextx, nexty, tail_x, tail_y, &dist2, &initDir);
                if(dist2 == -1) {
                    DestroyLife(game, life);
                    continue;
                }
                DestroyLife(game, life);
                if(mindist > dist) {
                    mindist = dist;
                    best_dir = dir;
                }
            }
        }
    }

    if(mindist == 999999999) {
        int dist;
        direction_t initDir = game->snake1->heading;
        int **life;
        life = InitLife(game);
        best_dir = bfs_tail(game, life, game->snake1->head->row, game->snake1->head->col, game->snake1->tail->row, game->snake1->tail->col, &dist, &initDir);
        DestroyLife(game, life);
        if(dist != -1 && game->snake1->head != game->snake1->tail)
            return best_dir;

        

        int row = game->snake1->head->row;
        int col = game->snake1->head->col;
        if(game->board->cells[(row + 1) * game->board->cols + col] == CELL_OPEN && game->snake1->heading != NORTH)
            return SOUTH;
        if(game->board->cells[(row - 1) * game->board->cols + col] == CELL_OPEN && game->snake1->heading != SOUTH)
            return NORTH;
        if(game->board->cells[row * game->board->cols + col + 1] == CELL_OPEN && game->snake1->heading != WEST)
            return EAST;
        return WEST;
    }
    return best_dir;

    
}