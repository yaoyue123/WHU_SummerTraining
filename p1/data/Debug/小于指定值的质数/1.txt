#include <stdio.h>
int main() {
    int a,b,c,d;
    scanf("%d",&a);
    for(d=1;d<=a;d+=1){
        for(b=1;b<d;b+=1){
            c=0;
            if(d%b==0){
             c+=1;
            }
        }
        if(c==0){
            printf("%d\n",d);
        }
    }
   
        
    return 0;
}