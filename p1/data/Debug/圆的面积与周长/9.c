#include <stdio.h>
#define PI 3.14159
int main() {
	float r;
    float c, s;
	scanf("%g", &r);
    c = 2 * PI * r;
    s = PI * r *r;
    printf("%.3f\n",c);
    printf("%.3f\n",s);
    return 0;
}