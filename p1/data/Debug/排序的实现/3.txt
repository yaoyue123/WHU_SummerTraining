#include <stdio.h>
#include <math.h>
int main() {
    int n = 10;
    int m;
    int numbers[100];
    int i;
    
void swap(int*a,int*b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
    // 读入给定的数字
    for (i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
        if(numbers[i]>numbers[i+1]){
            swap(numbers[i],numbers[i-1]);
        }
    }
    
    for(m=0;m<10;m++){
        printf("%d",numbers[m]);
        if(m!=9){
            printf(" ");
        }
    }
    return 0;
}
