#include<stdio.h>
#include<math.h>
int main() {
	int Year, Month, Day;
	scanf("%d-%d-%d", &Year, &Month, &Day);
	if ((Month < 1) || (Month > 12)) { printf("NO"); }
	else if ((Month == 1) && ((Day < 1) || (Day > 31))) {
		printf("NO");
	}
	else if ((Month == 3) && ((Day < 1) || (Day > 31))) {
		printf("NO");
	}
	else if ((Month == 4) && ((Day < 1) || (Day > 30))) {
		printf("NO");
	}
	else if ((Month == 5) && ((Day < 1) || (Day > 31))) {
		printf("NO");
	}
	else if ((Month == 6) && ((Day < 1) || (Day > 30))) {
		printf("NO");
	}
	else if ((Month == 7) && ((Day < 1) || (Day > 31))) {
		printf("NO");
	}
	else if ((Month == 8) && ((Day < 1) || (Day > 31))) {
		printf("NO");
	}
	else if ((Month == 9) && ((Day < 1) || (Day > 30))) {
		printf("NO");
	}
	else if ((Month == 10) && ((Day < 1) || (Day > 31))) {
		printf("NO");
	}
	else if ((Month == 11) && ((Day < 1) || (Day > 30))) {
		printf("NO");
	}
	else if ((Month == 12) && ((Day < 1) || (Day > 31))) {
		printf("NO");
	}
	else if ((Year % 400 == 0) && Month == 2 && (Day < 1 || Day>29)) {
		printf("NO");
	}
	else if ((Year % 100 == 0 && Year % 400 != 0) && Month == 2 && (Day < 1 || Day>28)) {
		printf("NO");
	}
	else if ((Year % 4 == 0 && Year % 100 != 0) && Month == 2 && (Day < 1 || Day>29)) {
		printf("NO");
	}
	else {
		printf("YES");
	}

	return 0;
}