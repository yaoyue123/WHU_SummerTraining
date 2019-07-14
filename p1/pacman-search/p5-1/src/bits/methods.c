#include "stdc++.h"


int max(int x, int y) {/*{{{*/
    return x > y ? x : y;
}/*}}}*/

int min(int x, int y) {/*{{{*/
    return x < y ? x : y;
}/*}}}*/

void swap(int *x, int *y) {/*{{{*/
    int tmp = *x;
    *x = *y;
    *y = tmp;
}/*}}}*/

void read(graph *g, char name[]) {/*{{{*/
    freopen(name, "r", stdin);
    int u, v, w, flag = 0;
    while (scanf("%d %d %d", &u, &v, &w) != EOF) {
        //add(g, u, v, w, 's');
        if (u == 0 | v == 0) {
            flag = 1;
        }
        g->vid = max(g->vid, max(u, v));
    }
    g->vid += flag;
    fclose(stdin);
}/*}}}*/
