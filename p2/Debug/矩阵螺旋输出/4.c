#include <stdio.h>

void space(int a, int b);

int main() {
	int matrix[100][100];
	int m;
	int n;
	int i, j, a;
	scanf("%d %d", &m, &n);
	int mix = ((m >= n) ? n : m);
	int opration = 2 * mix - 1 + (m > n);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	int ker = 0;
	for (i = 1; i <= opration + 1; i++) {
		switch (i % 4) {
		case 1:
			for (a = i / 4 - 1; a < (n - i / 4); a++) {
				if (a == -1) {
					a++;
				}
				printf("%d", matrix[i / 4][a]);
				ker++;
				if (ker == m * n) {
					break;
				}
				space(ker, m * n);
			}
			break;
		case 2:
			for (a = (i / 4 + 1); a < (m - i / 4); a++) {
				printf("%d", matrix[a][n - i / 4 - 1]);
				ker++;
				if (ker == m * n) {
					break;
				}
				space(ker, m * n);
			}
			break;
		case 3:
			for (a = (i / 4 + 1); a < (n - i / 4); a++) {
				printf("%d", matrix[m - i / 4 - 1][n - a - 1]);
				ker++;
				if (ker == m * n) {
					break;
				}
				space(ker, m * n);
			}
			break;
		case 0:
			for (a = (i / 4); a < (m - i / 4 - 1); a++) {
				printf("%d", matrix[m - a - 1][i / 4 - 1]);
				ker++;
				if (ker == m * n) {
					break;
				}
				space(ker, m * n);
			}
			break;
		}
		if (ker == m * n)
			break;
	}
	return 0;
}

void space(int a, int b) {
	if (a != b) {
		printf(" ");
	}
}
