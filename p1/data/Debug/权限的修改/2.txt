#include <stdio.h>
#include <string.h>
int main() {
    int r = 0, w = 0, x = 0;
    char sign[3];
    char temp[2];
    scanf("s\n", sign);
    for (int i = 0; i < strlen(sign); i++) {
        if (sign[i] == r) {
            r = 1;
        }
        if (sign[i] == w) {
            w = 1;
        }
        if (sign[i] == x) {
            x = 1;
        }
    }
    
    while (scanf("s", temp) != EOF) {
        if (temp == +x) {
            x++;
        }
         if (temp == -x) {
            x--;
        }
         if (temp == +r) {
            r++;
        } 
        if (temp == -r) {
            r--;
        } if (temp == +w) {
            w++;
        } if (temp == -w) {
            w--;
        }
    }
    
    printf("d\n", r*4 + w*2 + x);

    return 0;
}