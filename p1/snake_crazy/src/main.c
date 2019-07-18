#include "ai.h"
#include "file.h"
#include "game.h"
#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int seed;
  srand((unsigned)(&seed));
  if (argc < 2) {
    printf("Usage: ./main file_name\n");
    exit(-1);
  }
  game_t *game = create_game(argv[1]);
  while (1) {
    if (argc == 2) {
      usleep(game->time_step * 1000000);
      display(game);
    }
    direction_t d1 = get_action1(game);
    direction_t d2 = get_action2(game);
    set_direction(game->snake1, d1);
    set_direction(game->snake2, d2);
    int z = next_frame(game);
    if (z >= 0) {
      char *ret_str[] = {"Draw", "Snake1 win\n", "Snake2 win\n"};
      printf("%s", ret_str[z]);
      break;
    }
  }
  destroy_game(game);
  return 0;
}
