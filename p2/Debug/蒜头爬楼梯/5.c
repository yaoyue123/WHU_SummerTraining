#include <stdio.h>

int main() {
	int n;
	int i;
	int step[51];
	step[1] = 1;
	step[2] = 1;
	step[3] = 1;
	step[4] = 1;
	scanf("%d", &n);
	for (i = 5; i <= n; i++) {
		step[i] = step[i - 2] + step[i - 3];
	}
	step[4] = 2;
	printf("%d", step[n]);
	return 0;
}