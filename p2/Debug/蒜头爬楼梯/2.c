#include <stdio.h>

int main() {
	int i, n;//总台阶数
	scanf("%d", &n);
	int step[51];//step[N]N级台阶的方法数
	step[0] = 0;
	step[1] = 0;
	step[2] = 1;
	step[3] = 1;
	step[4] = 1;
	for (i = 5; i <= n; i++) {
		step[i] = step[i - 2] + step[i - 3];
	}
	printf("%d", step[n]);
	return 0;
}