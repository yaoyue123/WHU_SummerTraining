#include <stdio.h>
int main() {
	int n, i, j;
	scanf("%d", &n);
	if (n == 2) {
		printf("2");
	}
	else {
		printf("2\n");
		for (j = 2; j <= n; j++) {
			for (i = 2; i < j; i++) {
				if (j % i == 0) {
					break;
				}
				else if (i == j - 1) {
					printf("%d\n", j);
				}
			}
		}
	}

	return 0;
}

