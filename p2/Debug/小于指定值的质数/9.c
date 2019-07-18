#include <stdio.h>

int main() {
	int a;
	int b;
	int c;
	int flag=1;
	scanf("%d", &a);
	printf("2\n");
	for (b = 3; b <= a; b++) {
		for (c = 2; c < b; c++) {
			if (b % c == 0) {
				flag=0;
				break;
			}
		}
		if(flag==1)
		printf("%d\n", b);	
	flag=1;
	}
	return 0;
}