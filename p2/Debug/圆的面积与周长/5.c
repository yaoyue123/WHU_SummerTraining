#include <stdio.h>
#define PI 3.14159

int main() {
	double radius, grith, area;
	scanf("%lf", &radius);
	grith = 2 * PI * radius;
	area = PI * radius * radius;
	printf("%.3lf\n", grith);
	printf("%.3lf", area);
	return 0;
}
