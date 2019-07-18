#include <stdio.h>

int main()
{
	int n, i, j;
	scanf("%d", &n);
	printf("2\n");
	for (i = 3; i <= n; i++)
	{
		for (j = 2; j < i; j++)
		{
			if (i % j == 0)
				break;
		}
		if (i == j)
			printf("%d\n", i);
	}
	return 0;
}