#include<stdio.h>
int main() {
	int Year, Month, Day;
	scanf("%d-%d-%d", &Year, &Month, &Day);

	if (Month == 2) {
		if (Year % 4 == 0 && Year % 100 != 0 || Year % 400 == 0) {
			if (Day >= 1 && Day <= 29)
				printf("YES");
			else
				printf("NO");
		}
		else {
			if (Day >= 1 && Day <= 28)
				printf("YES");
			else
				printf("NO");
		}
	}
	else if (Month == 1 || Month == 3 ||
		Month == 5 || Month == 7 ||
		Month == 8 || Month == 10 || Month == 12) {
		if (Day >= 1 && Day <= 31)
			printf("YES");
		else
			printf("NO");
	}
	else if (Month == 4 || Month == 6 || Month == 9 || Month == 11) {
		if (Day >= 1 && Day <= 30)
			printf("YES");
		else
			printf("NO");
	}
	else
		printf("NO");

	return 0;
}