#include <stdio.h>

int main() {
int n,i;
    int sum = 0;
    int arr[50];
    scanf("%d",&n);
    arr[0]=2;
    arr[1]=3;
for (i = 2; i <= n; i++) {
        
          arr[i] = arr[i-2] +arr[i-3];
    sum += 1;
    
    }
    printf("%d",sum+2);
    return 0;
}