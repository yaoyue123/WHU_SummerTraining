#include <stdio.h>
void add(char);
void delete(char);
int rwx = 0;
int main() {
    //initiation
    char temp;
    char input[4];
    scanf("%s",input);	
	for(int i = 0; i < 3; i++)
	{
		temp = input[i];
		if (temp == 'x') rwx = rwx + 1;
		if (temp == 'w') rwx = rwx + 2;
		if (temp == 'r') rwx = rwx + 4;
	}
	
    while (scanf("%c", &temp) != EOF) {
        scanf("%c", &temp);
        if (temp == '+') {
            scanf("%c", &temp);
            add(temp);
        }
        else {
            scanf("%c", &temp);
            delete(temp);
        }
    }
    //output
    printf("%d", rwx);
    return 0;
}
void add(char input) {
    if (input == 'r' ) 
		rwx = rwx + 4;

    else if (input == 'w' ) rwx = rwx + 2;
    else if (input == 'x' ) rwx = rwx + 1;
}
void delete(char input) {
    if (input == 'r' ) rwx = rwx - 4;
    else if (input == 'w' ) rwx = rwx - 2;
    else if (input == 'x' ) rwx = rwx - 1;
}
