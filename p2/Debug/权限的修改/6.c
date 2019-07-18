#include <stdio.h>
#include <string.h>
#include <math.h>
int main() {
    int output;
	int r = 0;
    int w = 0;
    int x = 0;
    char plus[2] = "+";
    char minus[2] = "-";
    char oprator[2];
    char rr[2] = "r";
    char ww[2] = "w";
    char xx[2] = "x";
	char input[3];
	oprator [1] = '\0';
    char in[4];
	scanf("%s", in);
	int i;
	for(i = 0; i < 3; i++)
	{
		if(in[i] == 'r' )
			r = 1;
		if(in[i] == 'w' )
			w = 1;
		if(in[i] == 'x' )
			x = 1;
	}
    while (scanf("%s", input) != EOF) {
        char str[2] ;
		str[0] = input[1];
		str[1] = '\0';
		oprator[0] = input[0];
        if (strcmp(str, rr) == 0){
            if (strcmp(oprator, plus) == 0){
                r = 1;
            }else if (strcmp(oprator, minus) == 0){
                r = 0;
            }
        }else if (strcmp(str, ww) == 0){
            if (strcmp(oprator, plus) == 0){
                w = 1;
            }else if (strcmp(oprator, minus) == 0){
                w = 0;
            }
        }else if(strcmp(str, xx) == 0){
            if (strcmp(oprator, plus) == 0){
                x = 1;
            }else if (strcmp(oprator, minus) == 0){
                x = 0;
            }
        }
		/*else if (strcmp(str, plus) == 0){
            oprator[0] = '+';
        }else if (strcmp(str, minus) == 0){
            oprator[0] = '-';
        }*/
    } 
    output = x * 1 + r * 4 + w * 2;
    printf("%d", output);
    
    
    return 0;
}
