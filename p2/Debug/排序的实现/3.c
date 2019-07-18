#include <stdio.h>

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n = 10;
    int m;
    int numbers[100];
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }
    for (m = 0; m < n; m++) {
        for (i = n - 1; i > m; i--) {
            if ( numbers[i - 1] < numbers[i]) {
                swap(&numbers[i - 1], &numbers[i]);
            }
        }
    }
    for (m = 0; m < 10; m++) {
        printf("%d", numbers[m]);
        if (m != 9) {
            printf(" ");
        }
    }
    return 0;
}
