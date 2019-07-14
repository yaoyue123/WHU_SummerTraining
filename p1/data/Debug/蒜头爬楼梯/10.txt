#include <stdio.h>
int f(int n){
    if(n<=3){return 1;}
    else{return f(n-2)+f(n-3);}
}
int main() {
    int n;
    scanf("%d", &n);
    printf("%d", f(n));
    return 0;
}