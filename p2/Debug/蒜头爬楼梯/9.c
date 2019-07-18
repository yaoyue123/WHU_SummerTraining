#include <stdio.h>

int main() {
	int n, i;
	int step_count[51];
	scanf("%d", &n);

	if (n >= 1 && n <= 3)
		printf("1");
	else
	{
		step_count[4] = 1;
		step_count[2] = 1;
		step_count[3] = 1;
		for (i = 5; i <= n; i++) {
			step_count[i] = step_count[i - 2] + step_count[i - 3];
		}
		printf("%d", step_count[n]);
	}

	return 0;
}
