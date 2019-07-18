#include <stdio.h>
#define PI 3.14159

int main() {
	double radius;
	double grith, area;
	scanf("%lf", &radius);
	grith = 2 * PI * radius;
	area = PI * radius * radius;
	printf("%.3lf\n", grith);
	printf("%.3lf\n", area);
	return 0;
}