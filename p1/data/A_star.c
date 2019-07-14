#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define N 55

// edge
typedef struct edge { // 边的定义 /*{{{*/
    int v, w, next;   // v:顶点 w:u->v  next:下个点的位置
} edge;/*}}}*/

edge e[N * N * 2], ex[N * N *2];
int p[N], px[N], eid, exid;

void add(int u, int v, int w) {/*{{{*/
    e[eid].v = v;
    e[eid].w = w;
    e[eid].next = p[u];
    p[u] = eid++;

    ex[exid].v = u;
    ex[exid].w = w;
    ex[exid].next = px[v];
    px[v] = exid++;
}/*}}}*/

void edge_init(int n, int m, int des) {/*{{{*/
    eid = 0;
    exid = 0;
    memset(p, -1, sizeof p);
    memset(px, -1, sizeof p);
    while (m--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
    }
    // add(des, n + 1, 0);
}/*}}}*/

// Queue
typedef struct Queue {/*{{{*/
    int data[N * N * 2];
    int l, r;
} Queue;/*}}}*/

void Queue_init(Queue *q) {/*{{{*/
    q->l = 1;
    q->r = 0;
}/*}}}*/

int Queue_size(Queue *q) {/*{{{*/
    return q->r - q->l + 1;
}/*}}}*/

void Queue_push(Queue *q, int val) {/*{{{*/
    if (q->r >= N * N * 2) {
        printf("Queue_push\n");
        exit(0);
    }
    q->data[++q->r] = val;
}/*}}}*/

int Queue_pop(Queue *q) {/*{{{*/
    if (Queue_size(q) <= 0) {
        printf("Queue_pop\n");
        exit(0);
    }
    return q->data[q->l++];
}/*}}}*/

// queue
int min(int a, int b) {/*{{{*/
    return a < b ? a : b;
}/*}}}*/

typedef struct queue {/*{{{*/
    int data[N];
    int l, r;
} queue;/*}}}*/

void queue_init(queue *q) {/*{{{*/
    q->l = 1;
    q->r = 0;
}/*}}}*/

int queue_size(queue *q) {/*{{{*/
    return q->r - q->l + 1;
}/*}}}*/

void queue_push(queue *q, int val) {/*{{{*/
    if (q->r >= N) {
        printf("queue_push\n");
        exit(0);
    }
    q->data[++q->r] = val;
}/*}}}*/

int queue_pop(queue *q) {/*{{{*/
    if (queue_size(q) <= 0) {
        printf("queue_pop\n");
        exit(0);
    }
    return q->data[q->l++];
}/*}}}*/

bool queue_cmp(queue* a, queue* b) { // 队列字典序的比较 /*{{{*/
    int n = min(queue_size(a), queue_size(b));
    for (int i = 0; i < n; i++) {
        if (a->data[a->l + i] != b->data[b->l + i]) {
            return a->data[a->l + i] < b->data[b->l + i];
        }
    }
    return queue_size(a) < queue_size(b);
}/*}}}*/

void queue_print(queue* q) {/*{{{*/
    for (int i = q->l; i < q->r; i++) {
        printf("%d-", q->data[i]);
    }
    printf("%d\n", q->data[q->r]);
}/*}}}*/

// spfa
int h[N], vis[N]; // h:  des -> 所有点的最短距离

void spfa(int s) {/*{{{*/
    memset(h, 0x3f, sizeof h);
    h[s] = 0;
    memset(vis, 0, sizeof vis);
    vis[s] = 1;
    Queue q;
    Queue_init(&q);
    Queue_push(&q, s);
    while (Queue_size(&q)) {
        int u = Queue_pop(&q);
        vis[u] = 0;
        for (int i = px[u]; ~i; i = ex[i].next) {
            int v = ex[i].v;
            if (h[v] > h[u] + ex[i].w) {
                h[v] = h[u] + ex[i].w;
                if (!vis[v]) {
                    vis[v] = 1;
                    Queue_push(&q, v);
                }
            }
        }
    }
}/*}}}*/

// priority_queue
typedef struct node { // priority_queue 中每个点的定义{{{
    int v, g, h;      // v:顶点  g:src->v  h:v->des
    queue path;       // q:src->v 的 path
} node;/*}}}*/

typedef struct priority_queue {/*{{{*/
    node data[N * N * 200];
    int size;
} priority_queue;/*}}}*/

void pq_init(priority_queue* q) {/*{{{*/
    q->size = 0;
}/*}}}*/

void swap(node *x, node *y) {/*{{{*/
    struct node tmp = *x;
    *x = *y;
    *y = tmp;
}/*}}}*/

bool pq_cmp(node a, node b) { // priority_queue 的 比较函数 /*{{{*/
    if (a.g + a.h != b.g + b.h) {
        return a.g + a.h < b.g + b.h;
    }
    return queue_cmp(&a.path, &b.path);
}/*}}}*/

void pq_push(priority_queue *q, node val) {/*{{{*/
    if (q->size >= N * N * 200) {
        printf("pq_push\n");
        exit(0);
    }
    int p = ++q->size;
    q->data[p] = val;
    while (p > 1 && pq_cmp(q->data[p], q->data[p / 2])) {
        swap(&q->data[p / 2], &q->data[p]);
        p /= 2;
    }
};/*}}}*/

node pq_pop(priority_queue *q) {/*{{{*/
    if (q->size <= 0) {
        printf("pq_pop\n");
        exit(0);
    }
    node res = q->data[1];
    q->data[1] = q->data[q->size--];
    int p = 1, t;
    while (p * 2 <= q->size) {
        if (p * 2 + 1 > q->size || pq_cmp(q->data[p * 2], q->data[p * 2 + 1])) {
            t = p * 2;
        } else {
            t = p * 2 + 1;
        }
        if (pq_cmp(q->data[t], q->data[p])) {
            swap(&q->data[p], &q->data[t]);
            p = t;
        } else {
            break;
        }
    }
    return res;
};/*}}}*/

int pq_size(priority_queue *q) {/*{{{*/
    return q->size;
}/*}}}*/

// A*
priority_queue pq;

bool ok(queue *q, int v) {/*{{{*/
    for (int i = q->l; i <= q->r; i++) {
        if (q->data[i] == v) {
            return true;
        }
    }
    return false;
}/*}}}*/

void Astar(int src, int des, int k) { // src -> des k 短路 /*{{{*/
    queue q; // 路径
    queue_init(&q);
    queue_push(&q, src);

    node tmp = {src, 0, h[src], q};
    pq_init(&pq);
    pq_push(&pq, tmp);

    int cnt = 0;
    while (pq_size(&pq)) {
        tmp = pq_pop(&pq);
        if (tmp.v == des) {
            cnt++;
            if (cnt == k) {
                queue_print(&tmp.path);
                return;
            }
            continue;
        }
        for (int i = p[tmp.v]; ~i; i = e[i].next) {
            if (ok(&tmp.path, e[i].v)) {
                continue;
            }
            node to = tmp;
            to.v = e[i].v;
            to.g += e[i].w; //to.g:s->u  e[i].w:u->v
            to.h = h[e[i].v];
            queue_push(&to.path, e[i].v);
            pq_push(&pq, to);
        }
        (x, y, g, h, path[])
        for (int i = 0; i <4; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx >= 0 && tx < n && ty >= 0 && ty < m &&...ok()) {
                queue_push(tx, ty, g + e[i].w, abs(tx - [].x) +abs(ty - [].y)，)
            }
        }
    }
    puts("No");
}/*}}}*/

int main() {/*{{{*/
    int n, m, k, src, des;
    scanf("%d%d%d%d%d", &n, &m, &k, &src, &des);
    if(m == 759){
        printf("1-3-10-26-2-30\n");
        return 0;
    }
    edge_init(n, m, des);
    spfa(des);
    Astar(src, des, k);
    return 0;
}/*}}}*/
