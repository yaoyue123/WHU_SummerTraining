#include <stdio.h>
#include <string.h>

int main() {
	int n, i, j;
	scanf("%d\n", &n);
	char names[n][101];
	char max[101];
	for (i = 0; i < n; i++) {
		gets(names[i]);
	}
	max == names[n - 1];
	for (i = 0; i < n; i++) {

		if (strlen(names[i]) > strlen(max)) {
			strcpy(max, names[i]);
		}
	}

	printf("%s\n", max);
	return 0;
}

