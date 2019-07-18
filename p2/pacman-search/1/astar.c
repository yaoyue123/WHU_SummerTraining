#include <stdio.h>
#include <stdlib.h> 
#include <malloc.h>
#include <math.h>
#include <string.h>
#include "util.h"
# define M 100
# define N 100
#define MAXSIZE 10050

typedef struct node1 {
	int x;
	int y;
}point;

typedef struct node2 {
	point  p;
	struct node2 * from;
	int H, F, G;
	int visited;
}close;//封闭表

//初始化封闭表
void initClose(close cls[M + 1][N + 1],int startx,int starty,int endx,int endy) {
	int i, j;
	for (i = 1; i <= M; i++) {
		for (j = 1; j <= N; j++) {
			cls[i][j].p.x = i;
			cls[i][j].p.y = j;
			cls[i][j].visited = 0;
			cls[i][j].G = cls[i][j].F = 0;
			cls[i][j].H = abs(i - endx) + abs(j - endy);//曼哈顿距离
		}
	}
	cls[startx][starty].F = cls[startx][starty].H;//起点评估值
}

typedef struct node3 {
	int len;
	close *  arr[MAXSIZE];
}open;

//初始化open表
void initOpen(open * op){
	op->len = 0;
}

//入优先队列
void pushOpen(open * op,close cls[M+1][N+1],int x,int y,int g) {
	int i, minFlag=op->len;
	close * t;
	cls[x][y].G = g;
	cls[x][y].F = g + cls[x][y].H;
	op->arr[op->len++] = &(cls[x][y]);
	for (i = 0; i < op->len-1; i++) {
		if (op->arr[i]->F < op->arr[minFlag]->F)
			minFlag = i;
	}
	t=op->arr[minFlag];
	op->arr[minFlag] = op->arr[op->len - 1];
	op->arr[op->len - 1] = t;
}

void sortOpen(open * op) {
	int minFlag;
	int i;
	close *t;

	minFlag = op->len - 1;
	for (i = 0; i < op->len - 1; i++) {
		if (op->arr[i]->F < op->arr[minFlag]->F)
			minFlag = i;
	}
	t = op->arr[minFlag];
	op->arr[minFlag] = op->arr[op->len - 1];
	op->arr[op->len - 1] = t;
}

//出队
close * popOpen(open * op) {
	return op->arr[--op->len];
}

void printshortest(close cls[M + 1][N + 1], point start, point end) {
	close * steps[MAXSIZE];
	int flag = 1;
	int i;

	steps[0] = cls[end.x][end.y].from;
	for (i = 1;; i++) {
		steps[i] = steps[i - 1]->from;
		flag = i + 1;
		if (steps[i]->p.x == start.x&&steps[i]->p.y == start.y)
			break;
	}
	int tempx = start.x;
	int tempy = start.y;
	for (i = flag -1; i >= 0; i--) {
		if(steps[i]->p.x-tempx==1&&steps[i]->p.y-tempy==0) {
				printf("S");
		}
		else if(steps[i]->p.x-tempx==0&&steps[i]->p.y-tempy==1) {
			printf("E");
		}
		else if(steps[i]->p.x-tempx==-1&&steps[i]->p.y-tempy==0) {
			printf("N");
		}
		else if(steps[i]->p.x-tempx==0&&steps[i]->p.y-tempy==-1) {
			printf("W");
		}
		else{

		}
		tempx=steps[i]->p.x;
		tempy=steps[i]->p.y;
	}
	if(end.x-tempx==1&&end.y-tempy==0) {
				printf("S");
	}
	else if(end.x-tempx==0&&end.y-tempy==1) {
		printf("E");
	}
	else if(end.x-tempx==-1&&end.y-tempy==0) {
		printf("N");
	}
	else if(end.x-tempx==0&&end.y-tempy==-1) {
		printf("W");
	}
	else{

	}
	
}

int within(int x, int y) {
	if (x >= 1 && x <= M && y >= 1 && y <= N)
		return 1;
	else
		return 0;
}
int getshortest(int maze[M + 2][N + 2], point start, point end) {
	close cls[M + 1][N + 1];
	open op;
	close * c;
	int x0, y0;//当前位置
	int x1, y1,g1;//子节点
	int i, j;
	
	point dir[4];
	dir[0].x = 0; dir[0].y = 1;//向右
	dir[1].x = 0; dir[1].y = -1;//向左
	dir[2].x = 1; dir[2].y = 0;//向下	
	dir[3].x = -1; dir[3].y = 0;//向上
	
	initOpen(&op);
	initClose(cls,start.x,start.y,end.x,end.y);
	cls[start.x][start.y].visited = 1;
	
	pushOpen(&op, cls, start.x, start.y, 0);
	while (op.len!=0) {
		c = popOpen(&op);
		x0 = c->p.x;
		y0 = c->p.y;

		if (c->H == 0) {
			printshortest(cls,start,end);
			return 1;
		}
		for (i = 0; i < 4; i++) {
			x1 = x0 + dir[i].x;
			y1 = y0 + dir[i].y;
			if (within(x1, y1) == 1 && maze[x1][y1]==0) {
				if (cls[x1][y1].visited == 0) {
					cls[x1][y1].visited = 1;
					cls[x1][y1].from = c;
					g1= cls[x0][y0].G + 1;
					pushOpen(&op, cls, x1, y1, g1);
				}
				else {
					for (j = 0; j < op.len - 1; j++) {
						if (op.arr[j]->p.x == x1&&op.arr[j]->p.y == y1&&cls[x0][y0].G + 1+cls[x0][y0].H < op.arr[j]->G) {
							op.arr[j]->F = cls[x0][y0].G + 1 + cls[x0][y0].H;
							op.arr[j]->from = &(cls[x0][y0]);
							sortOpen(&op);
						}
					}
				}
			}
			else
				continue;
		}
	}
	printf("x");
	return 0;
}



int main(void) {

	int maze[M + 2][N + 2] ;
	game_state_t state;
	memset(&state, 0, sizeof(state));
	 init(&state);
	for(int i=0;i<state.n;i++)
		for(int j=0;j<state.m;j++) {
			maze[i][j]=state.grid[i][j];
		}
	point start, end;
	start.x = state.start_x;
	start.y = state.start_y;
	end.x = state.goal_x;
	end.y = state.goal_y; 

	getshortest(maze, start, end);
	destroy(&state);	
	return 0;
}