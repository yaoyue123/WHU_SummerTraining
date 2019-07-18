//该程序所有图的邻接表定义均使用李春葆《数据结构教程》第五版

#ifndef _STATS_H
#define _STATS_H

#define MAXV 420000 
#define INF  147483647
typedef int InfoType;
typedef struct ANode {
	int adjvex;					//该边的邻接点编号
	struct ANode* nextarc;		//指向下一条边的指针
	int weight;					//该边的相关信息，如权值（用整型表示）
} ArcNode;						//边结点类型
typedef struct Vnode {
	InfoType info;				//顶点其他信息
	int count;					//存放顶点入度,仅仅用于拓扑排序
	int temph, tempg;			//AStar算法所用
	int dis;
	ArcNode* firstarc;			//指向第一条边
} VNode;						//邻接表头结点类型
typedef struct {
	VNode adjlist[MAXV];		//邻接表头结点数组
	int n, e;					//图中顶点数n和边数e
} AdjGraph;						//完整的图邻接表类型

int cmp(const void* a, const void* b);
void initmaps(char name[]);
void DispAdj();//输出邻接表G
int numberOfEdges(char name[]);
int numberOfVertices(char name[]);
double freemanNetworkCentrality(char name[]);
double betweennessCentrality(char name[],char node[]);
double closenessCentrality(char name[],char node[]);
double eigenvectorCentrality(char name[],char node[]);
int bellman_ford1(int start, AdjGraph* g);

#endif
