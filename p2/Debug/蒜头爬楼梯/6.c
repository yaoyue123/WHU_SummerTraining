#include <stdio.h>

int main() {
	int n;
	int i;
	int step[51];
	step[2] = 1;
	step[3] = 1;
	step[4] = 1;
	scanf("%d", &n);
	if (n <= 4) {
		printf("%d", step[n]);
		return 0;
	}
	for (i = 5; i < n; i++) {
		step[i] = step[i - 2] + step[i - 3];
	}
	printf("%d", step[n - 2] + step[n - 3]);
	return 0;
}