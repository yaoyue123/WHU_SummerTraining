#include <stdio.h>

int main() {
	int matrix[100][100];
	int m, n, i, j, k = 0;
	scanf("%d%d", &m, &n);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	int start = 0, column = n, row = m;
	while (start < column && start < row) {
		if (n == 1) {
			for (i = 0; i < m; i++) {
				if (i == m - 1) {
					printf("%d", matrix[i][0]);
				} else {
					printf("%d ", matrix[i][0]);
				}
			}
		} else  if (m == 1) {
			for (j = 0; j < n; j++) {
				if (j == n - 1) {
					printf("%d", matrix[0][j]);
				} else {
					printf("%d ", matrix[0][j]);
				}
			}
		} else {
			for (j = start; j < column; j++) {
				if (k == m * n) {
					break;
				}
				printf("%d ", matrix[start][j]);
				k++;
				if (k == m * n) {
					break;
				}
			}
			for (i = start + 1; i < row; i++) {
				if (k == m * n) {
					break;
				}
				printf("%d ", matrix[i][column - 1]);
				k++;
				if (k == m * n) {
					break;
				}
			}
			for (j = column - 2; j >= start; j--) {
				if (k == m * n) {
					break;
				}
				printf("%d ", matrix[row - 1][j]);
				k++;
				if (k == m * n) {
					break;
				}
			}
			for (i = row - 2; i > start; i--) {
				if (k == m * n) {
					break;
				}
				printf("%d ", matrix[i][start]);
				k++;
				if (k == m * n) {
					break;
				}
			}
		}
		start++;
		column--;
		row--;
		if (k == m * n) {
			break;
		}
	}
	return 0;
}
