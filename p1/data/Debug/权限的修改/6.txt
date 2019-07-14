#include <stdio.h>
#include <string.h>

int main() {
    int r = 0;
    int w = 0;
    int x = 0;
    char plus[2] = "+";
    char minus[2] = "-";
    char oprator[2] = "@";
    char rr[2] = "r";
    char ww[2] = "w";
    char xx[2] = "x";
    
    char input;
    
    while (scanf("%c", &input) != EOF) {
        char str[2] = "\0";
        str[0] = input;
        if (strcmp(str, rr) == 0){
            if (strcmp(oprator, plus)){
                r = 1;
            }else if (strcmp(oprator, minus)){
                r = 0;
            }else{
                r = 1;
            }
        }else if (strcmp(str, ww) == 0){
            if (strcmp(oprator, plus)){
                w = 1;
            }else if (strcmp(oprator, minus)){
                w = 0;
            }else{
                w = 1;
            }
        }else if(strcmp(str, xx) == 0){
            if (strcmp(oprator, plus)){
                x = 1;
            }else if (strcmp(oprator, minus)){
                x = 0;
            }else{
                x = 1;
                
            }
        }else if (strcmp(str, plus) == 0){
            oprator[0] = '+';
        }else if (strcmp(str, minus) == 0){
            oprator[0] = '-';
        }
    }
    
    int output = x * pow(2,0) + w * pow(2,1) + r * pow(2,2);
    printf("%d", output);
    
    
    return 0;
}