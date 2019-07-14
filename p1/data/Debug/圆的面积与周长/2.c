#include <stdio.h>
#define PI 3.14159
int main() 
{
	float r;
	scanf("%lf\n", &r);
    printf("%.3f\n", PI * r * 2);
    printf("%.3f", PI * r * r);
        
    return 0;
}