#include <stdio.h>

int main() {
	int matrix_a[10][10];
    int matrix_b[10][10];
	int matrix_c[10][10];
	int m;
	int n;
	int i, j, k;
	for (i = 0; i < 10; i++) {
		for (k = 0; k < 10; k++) {
			matrix_c[i][k] = 0;
		}
	}
	scanf("%d %d", &m, &n);
	for (i = 0; i < m; i++) {
		for (k = 0; k < n; k++) {
			scanf("%d", &matrix_a[i][k]);
		}
	}
	for (k = 0; k < n; k++) {
		for (i = 0; i < m; i++) {
			scanf("%d", &matrix_b[k][i]);
		}
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			for (k = 0; k < n; k++) {
				matrix_c[i][j] += (matrix_a[i][k] * matrix_b[k][j]);
			}
		}
	}
	for (i = 0; i < m; i++) {
			for (k = 0; k < m; k++) {
				printf("%d", matrix_c[i][k]);
				if (k < m - 1 ) {
					printf(" ");
				}
				if (i == m - 1) {
					continue;
				}
				if (k == m - 1) {
					printf("\n");
				}
			}
		}
	return 0;
}	