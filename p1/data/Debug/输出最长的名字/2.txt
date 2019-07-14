#include <stdio.h>
#include <string.h>
int main() {
    int n;
    scanf("%d\n", &n);
    char names[n][101];
    char max[101];
    
    for (int i = 0; i < n; i++) {
         gets(names[i]);
    } 
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            max == names[j+1];
            if (strlen(names[j]) > strlen(names[j+1])) {
                strcpy(max, names[j]);
                strcpy(names[j], names[j+1]);
                strcpy(names[j], max);
            }
        }
    }
    
    printf("%s\n", max);
    return 0;
}