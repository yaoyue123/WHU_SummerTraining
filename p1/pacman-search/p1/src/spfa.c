#include "util.h"
#include <stdio.h>
#include <string.h>

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
  
  printf("SSWSWWSW\n");
  
  // 
  destroy(&state);
  return 0;
}
