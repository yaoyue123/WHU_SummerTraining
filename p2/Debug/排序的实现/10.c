#include <stdio.h>

int main() {
    int n = 10;
    int m;
    int numbers[10];
    int i;
    int max;
    int k;
    int j;
    int o;
    for (i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }
    for (j = 0; j < n - 1; j++) {
        for (k = 0; k < n - 1 - j; k++) {
            if (numbers[k] < numbers[k + 1]) {
                m = k + 1;
                o = numbers[k];
        		numbers[k] = numbers[m];
        		numbers[m] = o;
			}
        }
    }
    for (int q = 0; q < n; q++) {
        if (q == 9) {
            printf("%d", numbers[q]);
        } else {
            printf("%d ", numbers[q]);
        }
    }
    return 0;
}
