#include <stdio.h>
#include <string.h>

int main() {
	int n, i, j;
	scanf("%d\n", &n);
	char name[100][101]={ '0' };
	for (i = 0; i < n; i++) {
		for (j = 0; j < 101; j++) {
			scanf("%c", &name[i][j]);
			if (name[i][j] == '\n') {
				name[i][j] = '\0';
				break;
			}
		}
	}
	char temp_str[200] = { '\0' };
	for (i = 0; i < n; i++) {
		if (strlen(name[i]) >= strlen(name[i + 1])) {
			strcpy(temp_str, name[i]);
			strcpy(name[i], name[i + 1]);
			strcpy(name[i + 1], temp_str);
		}
	}
	printf("%s", temp_str);
	return 0;
}