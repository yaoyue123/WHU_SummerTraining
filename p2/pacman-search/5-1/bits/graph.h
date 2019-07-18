#ifndef graphs
#define graphs

//#include "stdc++.h"

typedef struct edge { // 边的定义 /*{{{*/
    int v, w, next;   // v:顶点 w:u->v  next:下个点的位置
    char dir;
    int flag;       // 是否是豆子
} edge;/*}}}*/

typedef struct graph {// 图的定义 /*{{{*/
    int *p;  // 头指针
    edge *e;
    int eid; // 边数id
    int vid; // 顶点id
    int edge_cap, vertex_cap;
} graph;/*}}}*/

void graph_free(graph *g);

void add(graph *g, int u, int v, int w, char dir, int flag);

void graph_init(graph *g, int edge_cap, int vertex_cap);

#endif
