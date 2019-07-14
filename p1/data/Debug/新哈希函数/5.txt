
#include <stdio.h>
#include <string.h>

int main() {
    char arr[32];
    char str[32];
    int bits[32];
    char result[32];
    
    scanf("%s", &arr[32]);
    char input;
    int j = 0;
    
    for(int i = 0; i < 32; i++){
        arr[i] = 0;
    }
    
    while (scanf("%c", &input) != EOF) {
        char str[2] = "\0";
        str[0] = input;
        if (strcmp(str, "\n")){
            break;
        }else if(j >= 32){
            break;
        }
        arr[j] = (int)(input);
        j++;
    }
    
    for (int i = 0; i < 32; i++) {
        arr[(i+1) % 32] = arr[(i+1) % 32] + (int)(str[i]);
    }
    
    for (int i = 0; i < 32; i++) {
        bits[i] = (arr[31 - i]) ^ (arr[i] << 1);
        int b = (bits[i] % 85) + 34;
        result[i] = (char)b;
    }
    
    for (int i = 0; i < 32; i++) {
        printf("%c",result[i]);
    }
    return 0;
}