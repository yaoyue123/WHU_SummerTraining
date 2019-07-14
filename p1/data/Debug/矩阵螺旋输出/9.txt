#include <stdio.h>

int main() {
    int matrix[100][100];
    int m;
    int n;
    int nIndex;
    int mIndex;
    int matrixpass[110][110];
    int orientation = 0;
    int i;
    int j;
    int times;
    int p = 0;
    //输入参数
    scanf("%d %d", &m, &n);
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    //计数清零
    int k;
    int l;
    k = m;
    l = n;
    times = 0;
    mIndex = 0;
    nIndex = 0;
    for(i = 0; i < 110; i++){
        for(j = 0; j < 110; j++){
            matrixpass[i][j] = 0;
        }
    }
    if(times <= m * n){
        for(i = 0; i < 6; i++){
        if(orientation % 4 == 0){  //right
            while(matrixpass[mIndex][nIndex] == 0 && nIndex <= l - 1){
                printf("%d", matrix[mIndex][nIndex]);
                matrixpass[mIndex][nIndex] = 1;
                nIndex++;
                times++;
                if(times != m * n){
                    printf(" ");
                }
            }
            orientation++;
            mIndex++;
            nIndex--;  
        }
        if(orientation % 4 == 1){  //down
            while(matrixpass[mIndex][nIndex] == 0 && mIndex <= k - 1){
                printf("%d", matrix[mIndex][nIndex]);
                matrixpass[mIndex][nIndex] = 1;
                mIndex++;
                times++;
                if(times != m * n){
                    printf(" ");
                }
            }
            orientation++;
            mIndex--;
            nIndex--;
        }
        if(orientation % 4 == 2){  //left
            while(matrixpass[mIndex][nIndex] == 0 && nIndex >= p){
                printf("%d", matrix[mIndex][nIndex]);
                matrixpass[mIndex][nIndex] = 1;
                nIndex--;
                times++;
                if(times != m * n){
                    printf(" ");
                }
            }
            orientation++;
            mIndex--;
            nIndex++;  
        }
        if(orientation % 4 == 3){  //up
            while(matrixpass[mIndex][nIndex] == 0 && mIndex >= p + 1){
                printf("%d", matrix[mIndex][nIndex]);
                matrixpass[mIndex][nIndex] = 1;
                mIndex--;
                times++;
                if(times != m * n){
                    printf(" ");
                }
            }
            orientation++;
            mIndex++;
            nIndex++;  
        }
        k--;
        l--;
        p++;
      }
    }
    return 0;
}