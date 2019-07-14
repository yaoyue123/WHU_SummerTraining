#include <stdio.h>
int main() {
    int n;
    int i;
    int j;
    
    scanf ("%d", &n);
    for (i = n; i >= 1; i-- ) {
        for (j = i; j >= 1; j-- ) {
            printf("%d", j);
                if (j != n - i -1) {
                    printf(" ");
                    }
            }
            
           
        printf("\n");
        }
        
        


    return 0;
}