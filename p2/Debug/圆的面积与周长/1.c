#include <stdio.h>
#include <math.h>
#define PI 3.14159

double round(double r) {
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

int main() {
	double r;
	double grith;
	double area;
	scanf("%lf", &r);;
	grith = 2 * PI * r * 1000;
	printf("%.3f\n", (round(grith) / 1000));
	area = PI * r * r * 1000000;
	printf("%.3f", (round(area)) / 1000000);

	return 0;
}
