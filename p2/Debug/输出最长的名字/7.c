#include <stdio.h>
#include <string.h>

int main() {
	int n, i, j;
	scanf("%d", &n);
	char names[100][101]={ '\0' };
	char temp[101]={ '\0' };

	n = n + 1;
	for (i = 0; i < n; i++) {
		for (j = 0; j < 101; j++) {
			scanf("%c", &names[i][j]);
			if (names[i][j] == '\n') {
				break;
			}
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n - 1 - i; j++) {
			if (strlen(names[j]) < strlen(names[j + 1])) {
				strcpy(temp, names[j]);
				strcpy(names[j], names[j + 1]);
				strcpy(names[j + 1], temp);
			}
		}
	}
	for (j = 0; j < 100; j++) {
		if(names[0][j]!='\0')
			printf("%c", names[0][j]);
	
	}

	return 0;
}