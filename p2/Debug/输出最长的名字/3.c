#include <stdio.h>
#include <string.h>

int main() {
	int n;
	size_t max = 0;
	size_t current;
	char maxName[200];
	char name[200];
	scanf("%d\n", &n);

	for (int i = 0; i < n; ++i) {
		gets(name);
		current = strlen(name);
		if (current > max) {
			max = current;
			strcpy(maxName, name);
		}
	}
	printf(maxName);
	return 0;
}
