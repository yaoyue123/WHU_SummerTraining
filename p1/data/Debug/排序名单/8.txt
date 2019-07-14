#include <stdio.h>
#include <string.h>
int main() {
    char string[10][21];
    char str[21];
    int i, j;
    for(i = 0; i < 10; i++){
        for(j = 0; j < 21; j++){
            scanf("%c", &string[i][j]);
            if(string[i][j] = '\n'){
                string[i][j] = '\0';
                break;
            }
        }
    }
    for (i = 0; i < 9; i++){
        for (j = 0; j <= 9-i; j++){
            if (strcmp(string[j+1], string[j]) > 0){
                strcpy(str,string[j+1]);
                strcpy(string[j+1],string[j]);
                strcpy(string[j],str);
            }
        }
    }
    for (i = 0; i < 10; i++){
        for (j = 0; j < 21; j++){
            if (string[i][j] == '\0'){
                printf ("\n");
                break;
            }
            else{
                printf ("%c", string[i][j]);
            }
        }
    }
    return 0;
}