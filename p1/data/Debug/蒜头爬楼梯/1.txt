#include <stdio.h>
int cal_step(int a[], int n){
    return a[n] = a[n - 2] + a[n - 3];
}
int main() {
	int N;//总台阶数
    scanf("%d", &N);
    int step[50];//step[N]N级台阶的方法数
    step[0] = 0;
    step[1] = 0;
    step[2] = 1;
    step[3] = 1;
    for (int i = 4; i <= N; i++){
        step[i] = step[i - 2] + step[i - 3];
    }
    printf("%d", step[N]);
    return 0;
}