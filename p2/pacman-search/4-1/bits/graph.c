#include "stdc++.h"

void graph_free(graph *g) {/*{{{*/
    free(g->e);
    free(g->p);
}/*}}}*/

void add(graph *g, int u, int v, int w, char dir, int flag) {/*{{{*/
    g->e[g->eid].v = v;
    g->e[g->eid].w = w;
    g->e[g->eid].dir = dir;
    g->e[g->eid].flag = flag;
    g->e[g->eid].next = g->p[u];
    g->p[u] = g->eid++;
}/*}}}*/

void graph_init(graph *g, int edge_cap, int vertex_cap) {/*{{{*/
    g->eid = 0;
    g->vid = 0;
    g->edge_cap = edge_cap;
    g->vertex_cap = vertex_cap;
    g->p = (int*)malloc(sizeof(int) * vertex_cap);
    g->e = (edge*)malloc(sizeof(edge) * edge_cap);
    memset(g->p, -1, sizeof(int) * vertex_cap);
}/*}}}*/

