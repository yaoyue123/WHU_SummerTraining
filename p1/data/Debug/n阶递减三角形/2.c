#include <stdio.h>

int main(){
    int n;
    int i, j;
    scanf("%d", &n);
    for(i = n;i >= 1;i--){
        for(j = i-1; j >= 0;j--){
            if(j >= 1){
                printf("%d", j+1);
                printf(" ");
            }
            else{
                 printf("%d\n", j+1);
            }
        }
    }
    return 0;
}
