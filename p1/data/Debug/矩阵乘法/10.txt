#include <stdio.h>

int main() {
    int matrix_a[10][10];
    int matrix_b[10][10];
    int result[10][10];
    int m;
    int n;
    int i, j, k;
    int sum;
    scanf("%d %d", &m, &n);
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++)
        {
            result[i][j] = 0;
        }
    }
     
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            scanf("%d", &matrix_a[i][j]);
        }
    }
    
    for (j = 0; j < m; j++){
        for (i = 0; i < n; i++){
            scanf("%d", &matrix_b[i][j]);
        }
    }
    
   for(i = 0; i < m; i++){
        for(j = 0; j < m; j++){
            for(k = 0; k < n; k++)
            {
                result[i][j]+= (matrix_a[i][k] * matrix_b[k][j]);
            }
        }
   }
    
    
    for (i = 0; i < m; i++){
        for (j = 0; j < m; j++){
            printf("%d", result[i][j]);
            if (j != m - 1){
                printf(" ");
            }        
        }
        printf("\n");
    }
    
    return 0;
}