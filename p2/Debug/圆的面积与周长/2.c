#include <stdio.h>
#define PI 3.14159

int main()
{
	double radius;
	scanf("%lf", &radius);
	printf("%.3f\n", PI * radius * 2);
	printf("%.3f", PI * radius * radius);

	return 0;
}
