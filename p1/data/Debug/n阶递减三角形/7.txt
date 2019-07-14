#include <stdio.h>
int main()
{
    int i,j,n;
    sacnf("%d",&n);
    for(i=1;i<=n;i++)
        for(j=1,j<=2*(n-i+1)-1,j++)
            if(j%2==0)
                printf(" ");
            else
                printf("%d",n-i+1);
    return 0;
}