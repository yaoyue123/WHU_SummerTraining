#include <stdio.h>

int main() {
    int matrix_a[10][10];
    int matrix_b[10][10];
    int m;
    int n;
    int i, j, k;
    int temp;
    scanf("%d%d", &n, &m);
    int matrix_result[n][n];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &matrix_a[i][j]);
        }
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &matrix_b[i][j]);
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            temp = 0;
            for (k = 0; k < m; k++) {
                temp += matrix_a[i][k] * matrix_b[k][j];
            }
            matrix_result[i][j] = temp;
            if (j == n - 1) {
                printf("%d\n", matrix_result[i][j]);
            } else {
                printf("%d ", matrix_result[i][j]);
            }
        }
    }
    return 0;
}