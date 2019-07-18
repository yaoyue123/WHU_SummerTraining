#include <stdio.h>

int main() {
	int matrix[100][100];
	int m;
	int n;
	int i, j;
	scanf("%d%d", &m, &n);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	int k = 0;
	if (m == 1) {
		for (j = 0; j < n; j++) {
			printf("%d", matrix[0][j]);
			k++;
			if (k != m * n) {
				printf(" ");
			}
		}
	}
	else if (n == 1) {
		for (j = 0; j < m; j++) {
			printf("%d", matrix[j][0]);
			k++;
			if (k != m * n) {
				printf(" ");
			}
		}
	}
	else {
		for (i = 0; i < 2 * m; i++) {
			switch (i % 4) {
			case 0:
				for (j = i / 4; j < n - i / 4 - 1; j++) {
					printf("%d", matrix[i / 4][j]);
					k++;
					if (k == m * n) {
						break;
					}
					if (k != m * n) {
						printf(" ");
					}
					if (m % 2 == 1 && k == m * n - 1) {
						printf("%d", matrix[i / 4][j + 1]);
					}
				}
				break;
			case 1:
				for (j = i / 4; j < m - i / 4 - 1; j++) {
					printf("%d", matrix[j][n - 1 - i / 4]);
					k++;
					if (k == m * n) {
						break;
					}
					if (k != m * n) {
						printf(" ");
					}
					if (m % 2 == 1 && k == m * n - 1) {
						printf("%d", matrix[j][m - i / 4 - 1]);
					}
				}
				break;
			case 2:
				for (j = n - 1 - i / 4; j > i / 4; j--) {
					printf("%d", matrix[m - i / 4 - 1][j]);
					k++;
					if (k == m * n) {
						break;
					}
					if (k != m * n) {
						printf(" ");
					}
				}
				break;
			case 3:
				for (j = m - 1 - i / 4; j > i / 4; j--) {
					printf("%d", matrix[j][i / 4]);
					k++;
					if (k == m * n) {
						break;
					}
					if (k != m * n) {
						printf(" ");
					}
					if (m % 2 == 1 && n % 2 == 1 && k == m * n - 1) {
						printf("%d", matrix[j][i / 4 + 1]);
					}
				}
				break;
			}
			if (k == m * n) {
				break;
			}
		}
	}
	return 0;
}
