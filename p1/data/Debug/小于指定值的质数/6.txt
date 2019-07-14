#include <stdio.h>
int main() {
int a,b,c;
    scanf("%d",&c);
        
     for(b=2;b<=c;b++) { 
     for(a=2;a<b;a++){
     if(b%a==0){printf("");break;}
     }
        if (a>=b){printf("%d\n"),b;}
     }
    return 0;
}