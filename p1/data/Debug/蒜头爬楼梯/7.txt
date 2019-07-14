#include <stdio.h>

int main() {
    int i,N,x;
    int a[51] = {0};
    scanf("%d",&N);
    a[2] = 2;
    a[3] = 3;
    for(i = 3;i <= N;i++){
        a[i] = a[i - 2] + a[i - 3];
    }
    printf("%d",a[N]);
    return 0;
}