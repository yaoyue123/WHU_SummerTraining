#include <stdio.h>

int main() {
    int matrix_a[10][10];
    int matrix_b[10][10];
    int matrix_result[15][15];
    int m;
    int n;
    scanf("%d %d", &m, &n);
    int m_index;
    int n_index;
    int j;
    for (m_index = 0; m_index < m; m_index++) {
        for (n_index = 0; n_index < n; n_index++) {
            scanf("%d", &matrix_a[m_index][n_index]);
        }
    }
    for (n_index = 0; n_index < n; n_index++) {
        for (m_index = 0; m_index < m; m_index++) {
            scanf("%d", &matrix_b[n_index][m_index]);
        }
    }
    for (m_index = 0; m_index < m; m_index++) {
        for (n_index = 0; n_index < m; n_index++) {
        	matrix_result[m_index][n_index] = 0;
            for (j = 0; j < n; j++) {
                matrix_result[m_index][n_index] += matrix_a[m_index][j] * matrix_b[j][n_index];
            }

        }
    }
    for (m_index = 0; m_index < m; m_index++) {
        for (n_index = 0; n_index < m; n_index++) {
            printf("%d", matrix_result[m_index][n_index]);
            if (n_index == m - 1 && m_index != m - 1) {
                printf("\n");
            } else if (n_index != m - 1) {
                printf(" ");
            }
        }
    }
    return 0;
}