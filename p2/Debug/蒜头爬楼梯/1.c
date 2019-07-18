#include <stdio.h>

long int cal_Step(int a[], int n) {
	return a[n] = a[n - 2] + a[n - 3];
}
int main() {
	int n;//总台阶数
	scanf("%d", &n);
	int step[51];//step[N]N级台阶的方法数
	step[0] = 0;
	step[1] = 0;
	step[2] = 1;
	step[3] = 1;
	for (int i = 4; i <= n; i++) {
		//step[i] = step[i - 2] + step[i - 3];
		step[i] = cal_Step(step, i);
	}
	printf("%d", step[n]);
	return 0;
}