#include <stdio.h>

int main() {
    int n;
    scanf("%d",&n);
    int i=0;
    int x;
    int y;
    int m=1;
    int b=1;
    for(x = 0; x <= n / 2; x++){
        for(y = 0; y <= n / 3; y++){
            if(x * 2 + y * 3 == n){
                i++;
            }
        }
    }
    printf("%d",i);
    return 0;
}