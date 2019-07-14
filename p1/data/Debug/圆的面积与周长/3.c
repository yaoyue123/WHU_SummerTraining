#include <stdio.h>
#include <math.h>
#define PI 3.14159
int main() {
    double r;
    scanf("%f", &r);
    printf("%.3lf\n%.3lf", 2 * PI * r, PI * pow(r, 2));
    return 0;
}