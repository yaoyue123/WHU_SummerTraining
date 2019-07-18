#include <stdio.h>

int main() {
	int i, n;
	int step[51];
	step[2]=1; 
	step[3]=1;
	step[4]=1;
	scanf("%d", &n);
	if (n >= 1 && n <= 3)
		printf("1");
	else
	{
		for (i = 5; i <= n; i++) {
			step[i] = step[i - 2] + step[i - 3];
		}
		printf("%d", step[n]);
	}
	return 0;
}