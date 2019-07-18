#include <stdio.h>

int main() {
	int n, i;
	int sum = 0;
	int step_count[51]={0};
	scanf("%d", &n);
	step_count[2] = 1;
	step_count[3] = 1;
	for (i = 3; i <= n; i++) {

		step_count[i] = step_count[i - 2] + step_count[i - 3];
		sum += step_count[i - 3];
	}
	if (n == 0 || n == 1)
		printf("0");
	else
		printf("%d", sum + 1);
	return 0;
}