#include<stdio.h>
#include<math.h>
int main() {
    int a,b,c;
 scanf("%d%d%d",&a,&b,&c);
    if((b<1)||(b>12)){printf("NO");}
    else if((b==1)&&((c<1)||(c>31))){printf("NO");}
     else if((b==3)&&((c<1)||(c>31))){printf("NO");}
     else if((b==4)&&((c<1)||(c>30))){printf("NO");}
     else if((b==5)&&((c<1)||(c>31))){printf("NO");}
     else if((b==6)&&((c<1)||(c>30))){printf("NO");}
     else if((b==7)&&((c<1)||(c>31))){printf("NO");}
     else if((b==8)&&((c<1)||(c>31))){printf("NO");}
    else if((b==9)&&((c<1)||(c>30))){printf("NO");}
    else if((b==10)&&((c<1)||(c>31))){printf("NO");}
    else if((b==11)&&((c<1)||(c>30))){printf("NO");}
    else if((b==12)&&((c<1)||(c>31))){printf("NO");}
    else if((a%400==0)&&b==2&&(c<1||c>29)){printf("NO");}
    else if((a%100==0||a%400!=0)&&b==2&&(c<1||c>28)){printf("NO");}
     else if((a%4==0||a%100!=0)&&b==2&&(c<1||c>29)){printf("NO");}
else {printf("YES");}
    
    return 0;    
}