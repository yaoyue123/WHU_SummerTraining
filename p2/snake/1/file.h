#ifndef FILE_H
#define FILE_H
#include "game.h"

game_t *create_game(const char *file_name);
void destroy_game(game_t *game);

#endif // FILE_H
