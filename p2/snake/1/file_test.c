#include "game.h"
#include "file.h"
#include <stdio.h>

void print(board_t *board) {
    for(int i = 0; i < board->rows; i++) {
        for(int j = 0; j < board->cols; j++) {
            switch(board->cells[i * board->cols + j]) {
                case CELL_OPEN:
                    printf("  ");break;
                case CELL_FOOD:
                    printf("💫");break;
                case CELL_WALL:
                    printf("⏩");break;
                case CELL_SNAKE:
                    printf("🐍");break;
            }
        }
        printf("\n");
    }
}

int main() {
    game_t *cur_game = create_game("../graph/simple.txt");
    char ch;
    print(cur_game->board);
    while((ch = getchar()) != 'q') {
        switch(ch) {
            case 'w':
                set_direction(cur_game->snake, NORTH);
                break;
            case 's':
                set_direction(cur_game->snake, SOUTH);
                break;
            case 'a':
                set_direction(cur_game->snake, WEST);
                break;
            case 'd':
                set_direction(cur_game->snake, EAST);
                break;
        }
        if(ch == '\n')
            continue;
        randomly_add_food(cur_game->board, cur_game->food_probability);
        if(1 == next_frame(cur_game)) {
            break;
        }
        print(cur_game->board);

    }
    destroy_game(cur_game);
    return 0;
}
