#ifndef _SEARCH_H
#define _SEARCH_H
#include "stats.h"

typedef struct {
	int data;	//顶点编号
	int parent;	//前一个顶点的位置
} QUERE;

typedef struct {
	int i;
	int j;
	int f;
} Side;

int *SPFA(AdjGraph* g, int start, int end);
void FindMinPath(AdjGraph* G, int u, int v, int path[], int* pathstep,
	int* length, int* minlength, int minpath[], int* minstep);
int *DFS(AdjGraph* G, int u, int v);
int *BFS(AdjGraph* G, int u, int v);
void Dispath(int dist[], int path[], int S[], int start, int end);
int *Dijkstra(AdjGraph* G, int start, int end);
int *shortestPath(int u, int v, char algorithm[], char name[]);
#endif
