#include <stdio.h>

int main(){
    int matrix[100][100];
    int m;
    int n;
    int i,j;
    int count=0;
    int max;
    
    //input m & n & matrix
    //printf("Enter the row & column of the matrix:");
	scanf("%d %d",&m,&n);
	//printf("\nEnter values in the matrix:\n");
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			scanf("%d",&matrix[i][j]);
			if(j<n-1)scanf(" ");
		}
	}
	max=m*n;
	
	//output the first line
	//printf("\nThe first line of the original matrix is:");
	for(j=0;j<n;j++){
		printf("%d ",matrix[0][j]);
		count++;
	}
	//printf("\n");
		
	do{	
		//printf("\nm=%d\nn=%d",m,n);//for debug
		int matrix_[n][m];//rotate the matrix to -90 degree which becomes matrix_
		//printf("\nDelete the first line,then rotate the matrix -90 degree.The remaining matrix_ is:\n");
		for(i=0;i<n;i++){
			for(j=0;j<m-1;j++){
				matrix_[i][j]=matrix[j+1][n-1-i];
				//printf("%d ",matrix_[i][j]);
			}
			//printf("\n");
		}
		
		/*if(m==1||n==1){
			break;
		}*/
		//printf("\nThe first line of the rotated matrix_ is:");
		for(j=0;j<m-1;j++){
			printf("%d",matrix_[0][j]);
			count++;
			if(count<max)printf(" ");
		}
	
		//cover original matrix with new matrix_	
		for(i=0;i<n;i++){
			for(j=0;j<m;j++){
				matrix[i][j]=matrix_[i][j];
			}
		}
		
		int t;
		t=m;
		m=n;
		n=t-1;
		//m=n;n=m-1; no use t.This is so wrong!!!
			
	}while(m>=1&&n>=1);
	
    return 0;
}