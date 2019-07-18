#include <stdio.h>

int main() {
    int n = 10;
    int m;
    int numbers[10];
    int i, j;
    int k;
    for (i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }
	for (j = 0; j < 9; j++) {
		for (k = 0; k < 9 - j; k++) {
			if (numbers[k] < numbers[k + 1]) {
				m = numbers[k];
				numbers[k] = numbers[k + 1];
				numbers[k + 1] = m;
			}
		}
	}
	for (i = 0; i < 10; i++) {
		printf("%d", numbers[i]);
		if (i < 9) {
			printf(" ");
		}
	}
    return 0;
}
