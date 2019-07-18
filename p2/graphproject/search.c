#include "stats.h"
#include "search.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern AdjGraph map;

int d[MAXV];
int que[MAXV];
int path[MAXV];
int visited[MAXV];
int visitbell[MAXV] = { 0 };
int *SPFA(AdjGraph* g, int start, int end) {
	int count = 1;
	int x;
	int antipath[MAXV] = {	0 };
	for (int i = 0; i < g->n; i++) {
		d[i] = INF;
		path[i] = -2;
	}
	d[start] = 0;
	path[start] = -1;
	int top = 1;
	int rear = 1;
	que[rear] = start;
	visitbell[start] = 1;
	rear++;
	while (rear > top) {
		int temp;
		temp = que[top];

		ArcNode* tempn;
		tempn = g->adjlist[temp].firstarc;
		while (tempn != NULL) {

			if (d[tempn->adjvex] > d[temp] + tempn->weight) {
				path[tempn->adjvex] = temp;
				d[tempn->adjvex] = d[temp] + tempn->weight;

				if (visitbell[tempn->adjvex] == 0) {
					visitbell[tempn->adjvex] = 1;
					que[rear] = tempn->adjvex;
					rear++;
				}

			}
			tempn = tempn->nextarc;

		}
		top++;
		visitbell[temp] = 0;
	}
	antipath[0]=-1;
	antipath[1]=end;
	count++;
	x = path[end];
	while (x != -1 && x != -2) {
		antipath[count] = x;
		x = path[x];
		count++;
	}
	//printf("%d", antipath[count - 1]);
	int *array = malloc(sizeof(int)*count + 1);
	int k=0;
	for (int i = count - 1; i >= 0; i--) {
		//printf("->%d", antipath[i]);
		array[k] = antipath[i];
		k++;
	}
	//printf("\n");
	//printf("cost:%d\n", d[end]);
	return array;
}


//↓↓↓DFS
void FindMinPath(AdjGraph* G, int u, int v, int path[], int* pathstep,
	int* length, int* minlength, int minpath[], int* minstep) {

	visited[u] = 1;
	(*pathstep)++;
	path[(*pathstep)] = u;
	if (u == v) {
		if ((*length) < (*minlength)) {
			(*minlength) = (*length);
			memcpy(minpath, path, sizeof(int) * ((*pathstep) + 1));
			(*minstep) = (*pathstep);
		}
		visited[u] = 0;
		(*pathstep)--;
		return;
	}
	ArcNode* ptr;
	ptr = G->adjlist[u].firstarc;
	//ArcNode *ptr = p -> nextarc;
	while (ptr != NULL) {
		if (visited[ptr->adjvex] == 0) {
			*length += ptr->weight;
			FindMinPath(G, ptr->adjvex, v, path, pathstep, length, minlength, minpath, minstep);
			(*length) -= ptr->weight;
		}
		ptr = ptr->nextarc;
	}
	visited[u] = 0;
	(*pathstep)--;
}

int* DFS(AdjGraph* G, int u, int v) {
	int minpath[MAXV];
	int path[MAXV];
	int minstep;
	int minlength = 0x3f3f3f3f;
	int length = 0;
	int pathstep = -1;
	FindMinPath(G, u, v, path, &pathstep, &length, &minlength, minpath, &minstep);
	int *array = (int *)malloc(sizeof(int)*minstep + 5);
	for (int i = 0; i <= minstep; i++) {
		//printf("%d -> ", minpath[i]);
		array[i] = minpath[i];
	}
	array[minstep+1]=-1;//array end sign
	//printf("NULL  weight : %d\n", minlength);
	return array;
}
//-----------------------------------------------------------------------------------
//↓↓↓BFS
int *BFS(AdjGraph* G, int u, int v) {
	int path[MAXV];
	int step = 0;
	int n;
	ArcNode* p;
	int w, i;
	QUERE qu[MAXV];
	int front = -1, rear = -1;
	int visited[MAXV];
	for (i = 0; i < G->n; i++) {
		visited[i] = 0;
	}
	rear++;
	qu[rear].data = u;
	qu[rear].parent = -1;
	visited[u] = 1;
	while (front != rear) {
		front++;
		w = qu[front].data;
		if (w == v) {
			i = front;
			while (qu[i].parent != -1) {
				step++;
				i = qu[i].parent;
			}
			n = step;
			i = front;
			while (qu[i].parent != -1) {
				path[step] = qu[i].data;
				i = qu[i].parent;
				step--;
			}
			path[0] = u;
			//printf("%d -> ", u);
			//for (int j = 1; j <= n; j++) {
			//	printf("%d -> ", path[j]);
			//}
			//printf("NULL  weight : %d\n", n);
			break;
		}
		p = G->adjlist[w].firstarc; 	//找w的第一个邻接点
		while (p != NULL) {
			if (visited[p->adjvex] == 0) {
				visited[p->adjvex] = 1;
				rear++;		 	//将w的未访问过的邻接点进队
				qu[rear].data = p->adjvex;
				qu[rear].parent = front;
			}
			p = p->nextarc;		//找w的下一个邻接点
		}
	}
	int *array = (int *)malloc(sizeof(int)*(n + 2));
	for(int i = 0; i <= n; i++) {
		array[i] = path [i];
	}
	array[n + 1] = -1;
	return array;
}
//-----------------------------------------------------------------------------
//↓↓↓Dijkstra
void Dispath(int dist[], int path[], int S[], int start, int end) {
	int j, k;
	int apath[MAXV];					//存放一条最短路径(逆向)及其顶点个数
	int d = 0;
	apath[d] = end;			//添加路径上的终点
	k = path[end];

	while (k != start) {
		d++;
		apath[d] = k;
		k = path[k];
	}
	d++;
	apath[d] = start;		//添加路径上的起点
	printf("%d ->", apath[d]);	//先输出起点
	for (j = d - 1; j >= 0; j--)	//再输出其他顶点
		printf(" %d ->", apath[j]);
	printf("NULL  weight : %d\n", dist[end]);


}

int *Dijkstra(AdjGraph* G, int start, int end) {
	int path[G->n];
	int dis[G->n];
	memset(path, -1, sizeof(int) * G->n);
	int c = 0;
	//初始化所有路径
	G->adjlist[start].dis = 0;
	ArcNode* s;
	s = G->adjlist[start].firstarc;
	while (s != NULL) {
		int v = s->adjvex;
		path[v] = start;
		G->adjlist[v].dis = s->weight;
		s = s->nextarc;
	}
	path[start] = 0;
	int ss[MAXV];
	int u[MAXV];
	int snum = 0;
	int unum = G->n;
	int i, j;
	G->adjlist[start].dis = 0;
	for (i = 0; i < unum; i++) {
		u[i] = i;
	}
	while (snum < G->n) {
		//找最近的点加入s，并从u删除
		int min = 0x3f3f3f3f;
		int index;
		for (i = 0; i < unum; i++) {
			int v = u[i];
			if (G->adjlist[v].dis < min && G->adjlist[v].dis != 0) {
				min = G->adjlist[v].dis;
				index = i;
			}
		}
		int v = u[index];
		ss[snum++] = v;//加入ss
		unum--;
		for (j = index; j < unum; j++)//从u中删除
		{
			u[j] = u[j + 1];
		}
		//重新附权值
		ArcNode* s;
		s = G->adjlist[v].firstarc;
		while (s != NULL) {
			if (G->adjlist[v].dis + s->weight < G->adjlist[s->adjvex].dis)
			{
				G->adjlist[s->adjvex].dis = G->adjlist[v].dis + s->weight;
				path[s->adjvex] = v;
			}
			s = s->nextarc;
		}
	}
	for (int q = 0; q < G->n; q++) {
		dis[q] = G->adjlist[q].dis;
	}
	Dispath(dis, path, ss, start, end);
}

int *shortestPath(int u, int v, char algorithm[], char name[]) {
	initmaps(name);
	char searchmethod[5][10] = { "DFS", "BFS", "Dijkstra", "SPFA", "Astar"};
	int *dis = (int *) malloc(sizeof(int) * (map.n + 10));
	if(strcmp(algorithm, searchmethod[0]) == 0) {
		return DFS(&map, u, v);
	}
	else if(strcmp(algorithm, searchmethod[1]) == 0) {
		return BFS(&map, u, v);
	}
	else if(strcmp(algorithm, searchmethod[2]) == 0) {
		return Dijkstra(&map, u, v);
	}
	else if(strcmp(algorithm, searchmethod[3]) == 0) {
		return SPFA(&map, u, v);
	}
	else if(strcmp(algorithm, searchmethod[4]) == 0) {

	}
}
