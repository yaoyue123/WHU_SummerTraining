#include <stdio.h>
#include <math.h>

int main() {
	int matrix[100][100];
	int m;
	int n;
	int i, j;
	int x;
	int k, p = 0;
	scanf("%d %d", &m, &n);
	k = m * n;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	x = 0;
	i = 0;
	j = 0;
	while (p != k) {
		for (x = j; x < n - 1 - j; x++) {
			printf("%d", matrix[i][x]);
			p++;
			if (p == k) {
				break;
			} else {
				printf(" ");
			}
		}
		for (x = i; x < m - 1 - i; x++) {
			printf("%d", matrix[x][n - 1 - j]);
			p++;
			if (p == k) {
				break;
			} else {
				printf(" ");
			}
		}
		for (x = j; x < n - 1 - j; x++) {
			printf("%d", matrix[m - 1 - i][n - 1 - x]);
			p++;
			if (p == k) {
				break;
			} else {
				printf(" ");
			}
		}
		for (x = i; x < m - 1 - i; x++) {
			printf("%d", matrix[m - 1 - x][j]);
			p++;
			if (p == k) {
				break;
			} else {
				printf(" ");
			}
		}
		i++;
		j++;
	}
	return 0;
}
