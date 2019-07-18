#include <stdio.h>
#include <string.h>

int main() {
	int n;
	char name[100][101]={ '\0' };
	char temp[101]={ '\0' };

	scanf("%d\n", &n);
	for (int i = 0; i < n; i++) {
		gets(name[i]);
	}

	for (int j = 0; j < n; j++) {
		for (int k = 0; k <= n - j; k++) {
			if ((strlen(name[k]) <= strlen(name[k + 1]))) {
				strcpy(temp, name[k]);
				strcpy(name[k], name[k + 1]);
				strcpy(name[k + 1], temp);
			}
		}
	}
	printf("%s\n", name[0]);
	return 0;
}