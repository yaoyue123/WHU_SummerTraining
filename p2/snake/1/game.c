#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "game.h"

board_t *create_board(int rows, int cols) 
{
    board_t *board = (board_t *)malloc(sizeof(board_t));
    board->rows = rows;
    board->cols = cols;
    board->cells = (cell_t *)malloc(sizeof(cell_t) * rows * cols);
    for(int index = 0; index < rows * cols; index++) {
        int now_row = index / cols;
        int now_col = index % cols;
        //if(now_row == 0 || now_row == rows - 1 || now_col == 0 || now_col == cols - 1) {
        //    board->cells[index] = CELL_WALL;
        //} else {
        //    board->cells[index] = CELL_OPEN;
        //}
        board->cells[index] = CELL_OPEN;
    }
    return board;
}

void destroy_board(board_t *board)
{
    free(board->cells);
    free(board);
}

cell_t *board_cell(board_t *board, int row, int col) {
    if(row >= board->rows || row < 0 || col >= board->cols || col < 0)
        return NULL;
    cell_t *cell_ptr = &(board->cells[row * board->cols + col]);
    return cell_ptr;
}

void destroy_snake(snake_t *snake) {
	snake_node_t *p = snake->head;
	snake_node_t *q = snake->head->next;
	while (p != snake->tail) {
		free(p);
		p = q;
		q = p->next;
	}
	free(p);
    free(snake);
}

snake_t *create_snake(board_t *board, int row, int col, direction_t heading) {
	snake_t	*snake = (snake_t *)malloc(sizeof(snake_t));
	snake_node_t *first = (snake_node_t *)malloc(sizeof(snake_node_t));
    first->row = row;
    first->col = col;
    first->next = NULL;
    snake->head=first;
    snake->tail=first;
    snake->heading = heading;
    board->cells[row*board->cols+col] = CELL_SNAKE;
    snake->growth = 0;
	return snake;
}

void randomly_add_food(board_t *board, float probability) 
{
    if((float)rand() / RAND_MAX > probability)
        return;
    int open_num = 0;
    for(int i = 0; i < board->rows * board->cols; i++) {
        if(board->cells[i] == CELL_OPEN)
            open_num++;
    }
    int index = rand() % open_num;
    int now_index = -1;
    for(int i = 0; i < board->rows * board->cols; i++) {
        if(board->cells[i] == CELL_OPEN)
            now_index++;
        if(now_index == index) {
            board->cells[i] = CELL_FOOD;
            break;
        }
    }
}

void update_snake_head(snake_t *snake, board_t *board, int growth_per_food)
{
    snake_node_t *node = (snake_node_t *)malloc(sizeof(snake_node_t));
    node->row = snake->head->row;
    node->col = snake->head->col;
    switch(snake->heading) {
        case EAST:
            node->col++;break;
        case WEST:
            node->col--;break;
        case NORTH:
            node->row--;break;
        case SOUTH:
            node->row++;break;
    }
    node->next = snake->head;
    snake->head = node;
    if(snake->growth > 0) {
        snake->growth--;
    }
    if(board->cells[node->row * board->cols + node->col] == CELL_FOOD) {
        snake->growth += growth_per_food;
    }
    board->cells[node->row * board->cols + node->col] = CELL_SNAKE;
}

void set_direction(snake_t *snake, direction_t d) {
	int a, b;
	a = (int)snake->heading;
	b = (int)d;
	if(abs(a - b) != 2)
	snake->heading = d;
}

void update_snake_tail(snake_t *snake, board_t *board) {
	if(snake->head->next == NULL){
		return;
	}
	if(snake->growth == 0) {
	snake_node_t *ptr, *ptr1;
	ptr = snake->head;
	while(ptr->next!=NULL) {
		ptr1=ptr;
		ptr=ptr->next;
		}
	ptr1->next = NULL;
	snake->tail = ptr1;
	board->cells[ptr->row * board->cols + ptr->col] = CELL_OPEN;
	free(ptr);
	}
}
int next_frame(game_t *cur_game){
    int head_row = cur_game->snake->head->row;
    int head_col = cur_game->snake->head->col;
    switch(cur_game->snake->heading) {
    case NORTH:
        head_row--;break;
    case SOUTH:
        head_row++;break;
    case WEST:
        head_col--;break;
    case EAST:
        head_col++;break;
    }
    randomly_add_food(cur_game->board, cur_game->food_probability);
    if(cur_game->board->cells[head_row * cur_game->board->cols + head_col] == CELL_WALL || 
    cur_game->board->cells[head_row * cur_game->board->cols + head_col] == CELL_SNAKE) {
        if(head_row == cur_game->snake->tail->row && head_col == cur_game->snake->tail->col && cur_game->snake->growth == 0) {
            update_snake_tail(cur_game->snake,cur_game->board);
            update_snake_head(cur_game->snake,cur_game->board,cur_game->growth_per_food);
            return 0;
        }
        return 1;
    } else {
		update_snake_head(cur_game->snake,cur_game->board,cur_game->growth_per_food);
		update_snake_tail(cur_game->snake,cur_game->board);
        return 0;
    }
}
