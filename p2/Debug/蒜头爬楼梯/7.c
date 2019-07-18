#include <stdio.h>

int main() {
	int i, n, x;
	int step[52] = { 0 };
	scanf("%d", &n);
	step[2] = 1;
	step[3] = 1;
	for (i = 3; i <= n + 2; i++) {
		step[i] = step[i - 2] + step[i - 3];
	}
	printf("%d", step[i - 1]);
	return 0;
}
