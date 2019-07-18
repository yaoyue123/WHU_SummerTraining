#include <stdio.h>
#include <string.h>

int main() {
	int arr[33] = { 0 };
	char input[1000];
	int bits[32];
	char result[33];
	int i = 1, j = 0;
	while (scanf("%c",&input[i - 1]) != EOF) {
		if (input[i - 1]!= '\n'){
		arr[i % 32] = arr[i % 32] + (int)input[i - 1];
		i++;
		}
	}

	for (j = 0; j <= 31; j++) {
		bits[j] = arr[31 - j] ^ (arr[j] << 1);
	}

	for (j = 0; j <= 31; j++) {
		result[j] =(char)((bits[j] % 85) + 34);
	}
	result[32] = '\0';
	puts(result);

	return 0;
}