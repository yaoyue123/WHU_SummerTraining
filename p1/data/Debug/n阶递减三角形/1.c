#include <stdio.h>

int main() {
    int n; 
    int i,j; 
    scanf ( "%d" , &n ) ;
    for(i = n; i >= 1; i--){
        for(j = i; j >= 1; j--){
            if(j > 1){
                printf("%d",j);
                printf(" ");
            }
            else{
                 printf("%d\n",j);
            }
        }
    }
    return 0;
}
