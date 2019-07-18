#include <stdio.h>

int main() {
	int matrix[100][100];
	int m;
	int n;
	int i;
	int j;
	int nindex;
	int mindex;
	int k;
	int l;
	nindex = 0;
	mindex = 0;
	k = m;
	l = n;
	scanf("%d %d", &m, &n);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	while (nindex * 2 < m && mindex * 2 < n) {
		k = m - 1 - nindex;
		l = n - 1 - mindex;
		if (mindex <= l) {
			for (j = mindex; j <= l; j++) {
				printf("%d", matrix[nindex][j]);
				if (j <= l) {
					printf(" ");
				}
			}
		}
		if (nindex <= k) {
			for (j = nindex + 1; j <= k; j++) {
				printf("%d", matrix[j][l]);
				if (j <= k) {
					printf(" ");
				}
			}
		}
		if (k > nindex && mindex < l) {
			for (j = l - 1; j >= mindex; j--) {
				printf("%d", matrix[k][j]);
				if (j >= mindex) {
					printf(" ");
				}
			}
		}
		if (k - 1 > nindex && mindex < l) {
			for (i = k - 1; i >= nindex + 1; i--) {
				printf("%d", matrix[i][nindex]);
				if (i >= nindex + 1) {
					printf(" ");
				}
			}
		}
		nindex++;
		mindex++;
	}
	return 0;
}

