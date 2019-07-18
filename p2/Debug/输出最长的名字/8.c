#include <stdio.h>
#include <string.h>

int main() {
	int n,i,j;
	char name[100][102];
	char largest_name[101]= { '\0' };
	scanf("%d\n", &n);
	for (i = 0; i < n; i++)
		for (j = 0; scanf("%c", &name[i][j]) != EOF && name[i][j] != '\n'; j++);

	for (strcpy(largest_name, name[0]), i = 1; i < n; i++)
		if (strlen(largest_name) < strlen(name[i]))
			strcpy(largest_name, name[i]);
	for (i = 0; i < 101; i++) {
        if(largest_name[i] != '\0' )
            printf("%c", largest_name[i]);
    }

	return 0;
}