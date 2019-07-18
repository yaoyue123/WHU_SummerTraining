#include "file.h"
#include <stdlib.h>
#include <stdio.h>
game_t *create_game(const char *file_name) {
	game_t *game = (game_t *)malloc(sizeof(game_t));
	int row, col, growth;
	float fps, probab;
	FILE *fp;
	fp = fopen(file_name,"r");
	if(fp == NULL) {
		printf("\nCan not find the file\n\n");
		exit(0);
	}
	fscanf(fp,"%d%d%f%f%d",&row,&col,&fps,&probab,&growth);
	game->board = create_board(row,col);
	game->time_step = fps;
	game->food_probability = probab;
	game->growth_per_food = growth;
	
	char elem;
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			fscanf(fp,"%c",&elem);
			if(elem == 'X') {
				game->board->cells[i*col+j] = CELL_WALL;
			} 
			else if(elem == '-') {
				game->board->cells[i*col+j] = CELL_OPEN;
			}
			else if(elem == '\n') {
			   j--;
			}
			else {
			    game->board->cells[i*col+j] = CELL_SNAKE;
				switch(elem) {
					case 'E': game->snake = create_snake(game->board, i, j, EAST);break;
					case 'S': game->snake = create_snake(game->board, i, j, SOUTH);break;
					case 'W': game->snake = create_snake(game->board, i, j, WEST);break;
					case 'N': game->snake = create_snake(game->board, i, j, NORTH);break;
				}
			}
		}
	}
	fclose(fp);
	return game;

}
void destroy_game(game_t *game) {
	destroy_board(game->board);
	destroy_snake(game->snake);
	free(game);
}
