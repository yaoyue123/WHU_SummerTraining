#include <stdio.h>
int main() {
    int n;
    int i,j;
    scanf("%d",&n);
    for(i = n;i >= 1;i--){
        for(j = i-1; j >= 1;j--){
            if(j >= 1){
                printf("%d",i);
                printf(" ");
            }
            else{
                 printf("%d\n",i);
            }
        }
    }
    return 0;
}