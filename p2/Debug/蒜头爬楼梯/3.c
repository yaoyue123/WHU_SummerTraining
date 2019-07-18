#include <stdio.h>

long long int count_Step(int n)
{
	if (n == 0 || n == 1)
		return 0;
	if (n == 2 || n == 3)
		return 1;
	else
		return count_Step(n - 2) + count_Step(n - 3);
}
int main() {
	long long int n;

	while (scanf("%d", &n) != EOF) {

		printf("%lld\n", count_Step(n));
	}
	return 0;
}
