#include "stdc++.h"
#include "search.h"

result bfs(graph *g, int src, int flag) { // bfs 搜索 
    result res;

    res.dis = (int*) malloc(sizeof(int) * (g->vertex_cap + 10));
    memset(res.dis, 0x3f, sizeof(int) * (g->vertex_cap + 10));
    res.dis[src] = 0;

    res.fa = (int*) malloc(sizeof(int) * (g->vertex_cap + 10));
    memset(res.fa, -1, sizeof(int) * (g->vertex_cap + 10));

    res.dir = (char*) malloc(sizeof(char) * (g->vertex_cap + 10));

    queue q;
    queue_init(&q, g->vertex_cap * 10);
    queue_push(&q, src);
    int cnt = 0;

    while (queue_size(&q)) {
        int u = queue_pop(&q);
        for (int i = g->p[u]; ~i; i = g->e[i].next) {
            int v = g->e[i].v;
            int w = g->e[i].w;
            if (res.dis[v] > res.dis[u] + w) {
                res.dis[v] = res.dis[u] + w;
                res.fa[v] = u;
                res.dir[v] = g->e[i].dir;
                queue_push(&q, v);
                if (flag && g->e[i].flag) {
                    res.pos = v;
                    return res;
                }
            }
        }
    }
    free(q.data);
    res.pos = -1;
    return res;
}

void print(int fa[], char dir[], int u) {
    if (fa[u] == -1) {
        return ;
    }
    print(fa, dir, fa[u]);
    //printf("%d\n", u);
    if (fa[fa[u]])
    printf("%c", dir[u]);
}

void result_free(result *res) {
    free(res->fa);
    free(res->dir);
    free(res->dis);
}
