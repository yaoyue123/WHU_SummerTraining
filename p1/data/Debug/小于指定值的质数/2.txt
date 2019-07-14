#include<stdio.h>
int main()
{
   int n,i,j;
    scanf("%d",&n);
   if(n==2)
   {
   printf("2\n");
   }
    else
        printf("2\n");
    {
        for(i=3;i<=n;i=i+1)
        {
            for(j=2;j<=i;j=j+1)
            {if(i%j==0)
                {
                    break;
                }
            else
            {
                printf("%d\n",i);
                break;
            }
            }
        }
    }
    return 0;
}
	