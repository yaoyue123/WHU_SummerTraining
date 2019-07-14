#include <stdio.h>
#include <string.h>

typedef struct edge {
    int v, w, next;
} edge;

edge e[10101];
int p[10101], eid;

void init() {
    eid = 0;
    memset(p, -1, sizeof p);
}

void add(int u, int v, int w) {
    e[eid].v = v;
    e[eid].w = w;
    e[eid].next = p[u];
    p[u] = eid++;
}

int p(queue *q, int *sum, int *cnt) {
    while (dis[front(q)] >= sum / cnt) {
        push(&q, pop(&q));
    }
    int v = pop(&q);
    sum -= dis[v];
    cnt--;
    return v;
}

queue q;
void spfa(int s) {
    memset(dis, 0x3f, sizeof dis);
    //memset(vis, 0, sizeof vis);
    dis[s] = 0;
    vis[s] = 1;
    push(&q, s);
    int sum = 0, cnt = 1;
    while (size(&q)) {
        int u = p(&q, &sum, &cnt);
        vis[u] = 0;
        for (int i = p[u]; ~i; i = e[i].next) {
            int v = e[i].v;
            int w = e[i].w;
            if (dis[v] > dis[u] + w) {
                int temp = dis[v];
                dis[v] = dis[u] + w;
                if (!vis[v]) {
                    sum += dis[v];
                    vis[v] = 1;
                    if (dis[front(&q)] > dis[v]) {
                        push_front(&q, v); // SLF
                    } else {
                        push_back(&q, v);
                    }
                    cnt++;
                }
                sum -= tmp - dis[v];
            }
        }
    }
}
int main() {
    init();
    spfa(b);
}
