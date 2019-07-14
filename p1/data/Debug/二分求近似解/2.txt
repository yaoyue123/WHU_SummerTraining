#include <stdio.h>
#include <math.h>
#define EPSILON 1e-7

double bisection(int p, int q, double (*func)(int, int, double));
double f(int p, int q, double x);
int main() {
    int p;
    int q;
    scanf("%d%d", &p, &q);
    printf("%.4f\n", bisection(p, q, f));
    return 0;
}

double bisection(int p, int q, double (*func)(int, int, double)) {
	double a = 20.0,b = -20.0;
    double m;
    while(1){
        m = (a + b) / 2;
        if(f(p,q,m) < EPSILON){
            return m;
        }else if(f(p,q,a) * f(p,q,m) < 0){
            a = m;
        }else{
            b = m;
        }
    }
}

double f(int p, int q, double x) {
    return p * x + q;
}