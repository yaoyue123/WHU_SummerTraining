#ifndef UTIL_H_
#define UTIL_H_

#define NORTH 'N'
#define SOUTH 'S'
#define WEST 'W'
#define EAST 'E'

typedef struct {
  int n, m;    
  int **grid;  
  int **food; 
  int start_x, start_y;
  int num_ghosts; 
  int *ghost_x, *ghost_y; 
  int index;
} game_state_t;

// init state from stdin, exec only once
void init(game_state_t *);

// free memory
void destroy(game_state_t *);

#endif // UTIL_H_