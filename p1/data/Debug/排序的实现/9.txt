#include <stdio.h>

void swap(int a, int b) {
    int c;
    if(a <= b){
        c = a;
        a = b;
        b = c;
    }
}

int main() {
    int n = 10;
    int m;
    int numbers[10];
    int i;
    
    // 读入给定的数字
    for (i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }
    for (i = 0; i < n; i++) {
        for(int j = 0; j < n - 1; j++) {
            swap(numbers[j], numbers[j + 1]);
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%d", numbers[i]);
        if(i != n - 1) printf(" ");
    }
    


    return 0;
}