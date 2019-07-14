#include <stdio.h>
int main(){
int i,j,n;
scanf("%d",&n);
for(i=1;i<=n;i++)
{
for(j=2;j<i;i++)
if(i%j==0)
    break;
if(j==i) {
    printf("%d\n",j);
}
}
    return 0;
}