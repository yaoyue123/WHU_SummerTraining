#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; n--) {
        for (int j = n; j >= i; j--) {
            printf("%d", j - i + 1);
            if (j > 1) {
                printf(" ");
            }
        }
        if (i < n) {
            printf("\n");
        }
    }
    return 0;
}
