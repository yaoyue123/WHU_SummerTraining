#include <stdio.h>
#include <math.h>
#define PI 3.14159
int main() {
	double radius;
	scanf("%lf", &radius);
	printf("%.3lf\n%.3lf", 2 * PI * radius, PI * radius * radius);
	return 0;
}