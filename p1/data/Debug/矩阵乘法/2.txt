#include <stdio.h>

int main() {
    int matrix_a[10][10];
    int matrix_b[10][10];
    int m;
    int n;
	scanf("%d %d",&m,&n);
    int i,j;
	for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%d",&matrix_a[i][j]);
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            scanf("%d",&matrix_b[i][j]);
        }
    }
    int matrix_c[10][10];
    int c;
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            for(c=0;c<n;c++){
                matrix_c[i][j]+=matrix_a[i][c]*matrix_b[c][j];
            }
        }
    }
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            if(j!=m-1){
            	printf("%d ",matrix_c[i][j]);
            }else{
                printf("%d\n",matrix_c[i][j]);
            }
        }
    }
    return 0;
}