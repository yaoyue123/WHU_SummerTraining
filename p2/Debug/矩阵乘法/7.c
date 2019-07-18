#include <stdio.h>

int main(void) {
    //declaration
    int mtxa[10][10], mtxb[10][10], mtxc[10][10], m, n;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            mtxc[i][j] = 0;
        }
    }
    //input
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &mtxa[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &mtxb[i][j]);
        }
    }
    //process
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            mtxc[i][j] = 0;
            for (int k = 0; k < n; k++) {
                mtxc[i][j] += mtxa[i][k] * mtxb[k][j];
            }
        }
    }
    //output
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            (j != m - 1) ? (printf("%d ", mtxc[i][j])) : (printf("%d", mtxc[i][j]));
        }
        printf("\n");
    }
    return 0;
}