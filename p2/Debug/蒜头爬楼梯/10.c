#include <stdio.h>

int countStep(int n) {
	if (n <= 3) {
		return 1;
	}
	else {
		return countStep(n - 2) + countStep(n - 3);
	}
}
int main() {
	int n;
	scanf("%d", &n);
	printf("%d", countStep(n - 1));
	return 0;
}
