# Snake Game

提供`file.h`和`game.h`

在相应的`file.c`和`game.c`实现所有函数，测试分别写在`file_test.c`和`game_test.c`

## game.h:
`board_t *create_board(int rows, int cols)`: 创建一个`rows`行`cols`列的board，初始化为`CELL_OPEN`

`void destroy_board(board_t *board)`: free掉board

`cell_t *board_cell(board_t *board, int row, int col)`: 获得`board`上`row`行`col`列元素的指针

`snake_t *create_snake(board_t *board, int row, int col, direction_t heading)`: 在board的`row`行`col`列创建一个蛇，初始方向是`heading`

`void destroy_snake(snake_t *snake)`: free掉snake

`void set_direction(snake_t *snake, direction_t d)`: 把`snake`的方向修改为`d`

`void randomly_add_food(board_t *board, float probability)`: 以概率`probability`在board上加一个食物，这个食物的位置在所有`CELL_OPEN`状态的cell等概率选。

`void update_snake_head(snake_t *snake, board_t *board, int growth_per_food)`: 模拟蛇走一步，更新蛇头

`void update_snake_tail(snake_t *snake, board_t *board)`: 模拟蛇走一步，更新蛇尾

`int next_frame(game_t *cur_game)`: 模拟蛇走一步，更新所有影响到的数据(snake, board)，存活返回0，撞死返回1

## file.h:
`game_t *create_game(const char *file_name)`: 根据文件初始化一个game，文件说明和example在graph文件夹

`void destroy_game(game_t *game)`: free掉game



