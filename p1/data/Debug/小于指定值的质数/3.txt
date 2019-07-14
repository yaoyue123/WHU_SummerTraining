#include <stdio.h>
#include <math.h>
int main() {
    int a;
    int b;
    int c;
    scanf("%d",&b);
    if (b == 1) {
    printf("");
    } else if (b == 2) {
    printf("2");
    } else if (b > 2) {
    printf("2\n3\n");
    for (a = 3;a <= b;a += 2) {
    for (c = 3;c <= a;c += 2) {
    if (a % c == 0 && a != c) {
    printf("");break;
    } else if (a % c == 0 && a == c) {
    printf("%d\n",a);
    }
    }
    }
    }
    return 0;
}