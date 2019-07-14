#include <stdio.h>
#include <string.h>

void f(char []);

int main()
{
    char string[500];
    
    scanf("%s", string);
    f(string);
    return 0;
}

void f(char string[])
{
    int arr[32], bits[32];
    char result[33];
    int i, j;
    unsigned long k;
    
    for (i = 0; i < 32; i++)
        arr[i] = 0;
    k = strlen(string);
    for (i = 1; i <= k; i++)
        arr[i % 32] += (int)string[i - 1];
    for (j = 0; j < 32; j++){
        bits[j] = arr[31 - j] ^ (arr[j] << 1);
        result[j + 1] = (char)(bits[j] % 85 + 34);
    }
    for (j = 0; j < 33; j++)
        printf("%c", result[j]);
}