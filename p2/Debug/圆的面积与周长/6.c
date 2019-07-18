#include<stdio.h>
#define PI 3.14159

int main() {
	double radius;
	scanf("%lf", &radius);
	printf("%.3lf\n", 2 * PI * radius);
	printf("%.3lf\n", PI * radius * radius);
	return 0;
}