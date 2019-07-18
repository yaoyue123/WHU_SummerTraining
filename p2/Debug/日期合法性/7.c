#include <stdio.h>
int main()
{
	int Year, Month, Date;
	int Leap_year, Date_valid, February_valid, Month30_valid, Month31_valid;
	scanf("%d-%d-%d", &Year, &Month, &Date);

	Leap_year = (((Year % 100 != 0 && Year % 4 == 0) || Year % 400 == 0) == 1 ? 1 : 0);  //1代表闰年，2月有29日
	February_valid = (Leap_year == 0 && Month == 2 && Date <= 28) || (Leap_year == 1 && Month == 2 && Date <= 29);
	Month30_valid = (Month == 4 || Month == 6 || Month == 9 || Month == 11) && (Date <= 30);
	Month31_valid = (Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12) && (Date <= 31);
	Date_valid = February_valid || Month30_valid || Month31_valid;
	//printf("%d\n%d\n%d\n",Month31valid,Month==1||3||5||7||8||10||12,Month==8);//调试用
	if (Date_valid == 1) {
		printf("YES");
	}
	else {
		printf("NO");
	}
	return 0;
}