#include <stdio.h>
#include <math.h>
#define PI 3.14159
int main() {
 double r;double a;double b;
scanf("%lf",r);;
a=2*PI*r*1000;
printf("%.3f\n",(round(a)/1000));
b=PI*r*r*1000000;
printf("%.3f",(round(b))/1000000);

    return 0;
}
