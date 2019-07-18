#include <stdio.h>

int main() {
	int num;
	scanf("%d", &num);
	int digit;
	int a;
	for (digit = 2; digit <= num; digit++)
	{
		for (a = 2; a <= digit; a++) {
			if (digit % a == 0) {
				break;
			}

		}
		if (a == digit) {
			printf("%d\n", digit);
		}
	}
	return 0;
}

