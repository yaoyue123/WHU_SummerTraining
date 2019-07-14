#include <stdio.h>
int main() {
    int arr[33] = {0};
    int bits[33];
   // char input[500];
    char input;
    char output[33];
    int i, j;
    int counter = 0;
    
    while (scanf("%c", &input) != EOF) {
        counter++;
        arr[counter % 32] += input;
    }
    
   // printf("arr = \n");
   // for(int i = 0; i < 32; i++) {
   //     printf("%d ", arr[i]);
   // }
   // printf("\n");
    
    for (j = 0; j < 32; j++) {
        bits[j] = arr[31 - j] ^ (arr[j] << 1);
    }
  //  printf("bits = \n");
  //  for(int i = 0; i < 32; i++) {
  //      printf("%d ", bits[i]);
  //  }
  //  printf("\n");
    for(int j = 0; j < 32; j++){
        output[j + 1] = (bits[j] % 85 + 34);
        printf("%c", output[j + 1]);
    }
    printf("\n");
    return 0;
}