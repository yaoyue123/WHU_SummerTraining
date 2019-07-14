#include <stdio.h>

int main() {
    int n = 10;
    int m;
    int numbers[10];
    int i,j;
    int tmpt;

    // 读入给定的数字
    for (i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }

    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            if (numbers[i] < numbers[j]){
                tmpt = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] =   tmpt;
            }
        }
    }

    for (int m = 0; m < 10; m++) {
        if (m != 9){
            printf("%d ", numbers[m]);
        }else{
            printf("%d", numbers[m]);
        }
        
    }

    return 0;
}