#include <stdio.h>
//#include <math.h>
#define PI 3.14159

double pow(double num, int count)
{
    double temp = 1;
    int i;
    for (i = 0; i < count; i++)
    {
        temp = temp * num;
    }
    return temp;
}

int main() {
    double radius;
    scanf("%lf", &radius);
    printf("%.3f\n%.3f", 2 * PI * radius, PI * pow(radius, 2));
    return 0;
}
