#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stats.h"
AdjGraph map;				//图的全局变量
int maxdegree;				//无向图最大度
double maxbetweenness;
double maxeigenvector;
int cmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b; //这是从小到大排序，若是从大到小改成： return *(int *)b-*(int *)a;
}
void initmaps(char name[]) {
	int u, v, w;
	FILE* fp;
	ArcNode* p;
	bool pointegde[MAXV] = { 0 }; //计算点数
	fp = fopen(name, "r");
	if (fp == NULL) {
		printf("\nCan not find the file\n\n");
		exit(0);
	}
	while (fscanf(fp, "%d%d%d", &u, &v, &w) != EOF) {
		map.adjlist[u].count++; //计算每个点的出度
		map.e++;				//计算图的边数
		pointegde[u] = 1;		//计算图的点数
		pointegde[v] = 1;		//计算图的点数
		maxdegree = map.adjlist[u].count > maxdegree ? map.adjlist[u].count : maxdegree;
		p = (ArcNode*)malloc(sizeof(ArcNode)); //创建一个结点p
		p->adjvex = v;
		p->weight = w;
		p->nextarc = map.adjlist[u].firstarc; //采用头插法插入结点p
		map.adjlist[u].firstarc = p;
		map.adjlist[u].dis = 0x3f3f3f3f;
	}
	for (int i = 0; i < MAXV; i++) {
		if (pointegde[i])
			map.n++;
	}
	fclose(fp);

}
//输出邻接表G
void DispAdj() {
	int i;
	ArcNode* p;
	for (i = 0; i < map.n; i++) {
		p = map.adjlist[i].firstarc;
		printf("%3d: ", i);
		while (p != NULL)
		{
			printf("%3d[%d]→", p->adjvex, p->weight);
			p = p->nextarc;
		}
		printf("∧\n");
	}
}
int bellman_ford1(int start, AdjGraph* g) {
	int d[g->n+5];
	int path[g->n+5];
	int pathdistance = 0;
	for (int i = 0; i < g->n; i++) {
		d[i] = INF;
		path[i] = -2;
	}
	d[start] = 0;
	path[start] = -1;
	for (int i = 0; i <= g->n; i++) {
		for (int j = 0; j <= g->n; j++) {
			ArcNode* temp;
			temp = g->adjlist[j].firstarc;
			while (temp != NULL) {

				if (d[temp->adjvex] > d[j] + temp->weight) {
					path[temp->adjvex] = j;
					d[temp->adjvex] = d[j] + temp->weight;
				}
				temp = temp->nextarc;
			}
		}
	}
	for (int i = 0; i <= g->n - 1; i++)
	{
		pathdistance += d[i];

	}

	return pathdistance;
}
int numberOfEdges(char name[]) {
	initmaps(name);
	//	ArcNode *p;
	//	int edges=0;
	//	for(int i=0;i<MAXV;i++) {			//maxv 用于得到遍历全部得到顶点数； 
	//		p=map.adjlist[i].firstarc;
	//		if(p!=NULL) {
	//			edges++;
	//		}
	//	}
	//	return edges;

	return map.e;
}
int numberOfVertices(char name[]) {
	initmaps(name);
	//	ArcNode *p;
	//	int vertices;
	//	for (int i=0;i<map.n;i++)
	//	{
	//		p=map.adjlist[i].firstarc;
	//		while (p!=NULL)
	//		{
	//			vertices++;
	//			p=p->nextarc;
	//		}
	//
	//	}
	//	return vertices;
	return map.n;
}
double freemanNetworkCentrality(char name[]) {
	initmaps(name);
	long long  sumfreeman = 0;
	double freeman;
	for (int i = 0; i < map.n; i++) {
		sumfreeman += (maxdegree - map.adjlist[i].count);
	}
	freeman = (double)(sumfreeman); 
	freeman = (freeman / ((map.n - 1) * (map.n - 2)));
	return freeman;
}
double betweennessCentrality(char name[],char node[]) {
	initmaps(name);
}
double closenessCentrality(char name[],char node[]) {
	initmaps(name);
	int sumdistance[50] = { 0	};
	if(strcmp(node,"max")==0) {
	for (int i = 0; i < map.n; i++) {
		sumdistance[i] = bellman_ford1(i, &map);
	}
	qsort(sumdistance, map.n, sizeof(sumdistance[0]), cmp);
	double maxcloseness = (double)sumdistance[0];
	maxcloseness = (map.n - 1) / maxcloseness;
	return (maxcloseness);
	}
	else {
	int i = atoi(node);
	double maxcloseness = bellman_ford1(i, &map);
	maxcloseness = (map.n - 1) / maxcloseness;
   	return (maxcloseness);
	}


}

double eigenvectorCentrality(char name[],char node[]) {
	initmaps(name);
}
