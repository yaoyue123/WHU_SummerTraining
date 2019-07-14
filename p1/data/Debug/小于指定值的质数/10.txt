#include <stdio.h>
int main()
{
    int N;
    int i,j;
    scanf("%d",&N);
    printf("2\n");
    for(i=3;i<N;i++)
    {   
        for(j=3;j<i;j++)
        {
           if(i%j==0)
               break;
        } 
        if(i==j)
            printf("%d\n",i);
    }      
    return 0;
}