#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

const double xmin = -5.0;
const double xmax = 5.0;


double funkcja(double x) {
    return exp(-(x * x));
}

double h(int n){
    return (xmax - xmin) / (double)n;
}

double lagraunge(double x, int n, double *xm, double *ym){
    double wielomian = 0.0;
    for(int i = 0; i <= n; i++) {
        double tmp = 1.0;
        for(int j = 0; j <= n; j++) {
            if(j!=i){
                tmp *= (x - xm[j]) / (xm[i] - xm[j]);
            }
        }
        wielomian += ym[i] * tmp;
    }
    return wielomian;
}

double czebyszew(int n, int m){
    return 0.5 * ( (xmax - xmin)* cos(PI*(2.0 * (double)m +1.0)/(2.0 * (double)n + 2.0) )
            + (xmin + xmax));
}


void wypelni(double *x, double *y, double *cx, double *cy, int n) {
    for(int i = 0; i <=n; i++){
        x[i] = y[i] = cx[i] = cy[i] = 0.0;
        x[i] = xmin + h(n) * i;
        y[i] = funkcja(x[i]);
        cx[i] = czebyszew(n, i);
        cy[i] = funkcja(cx[i]);
    }
}

void wypisz(double *x, double *y, int n) {
    for(int i = 0; i<=1000; i++) {
        double xZnaczenia = xmin + 0.01 * i;
        double wielomian = lagraunge(xZnaczenia, n, x, y);
        printf("%g %g\n",xZnaczenia, wielomian);
    }
    printf("\n\n");
}

void wypiszCzebyszew(double *cx, double *cy, int n) {
    for(int i = 0; i<=1000; i++) {
        double xZnaczenia = xmin + 0.01 * i;
        double wielomian = lagraunge(xZnaczenia, n, cx, cy);
        printf("%g %g\n",xZnaczenia, wielomian);
    }
    printf("\n\n");    
}

void wypiszXY(double *x, double *y, int n) {
    for(int i = 0; i <= n; i++) {
        printf("%g %g \n", x[i], y[i]);
    }
    printf("\n \n");
}

int main(void) {

    int n1 = 5;
    double x1[n1 +1];
    double y1[n1 +1];
    double cx1[n1+ 1];
    double cy1[n1 + 1];
    wypelni(x1, y1, cx1, cy1, n1);

    int n2 = 10;
    double x2[n2 +1];
    double y2[n2 +1];
    double cx2[n2+ 1];
    double cy2[n2 + 1];
    wypelni(x2, y2, cx2, cy2, n2);

    int n3 = 15;
    double x3[n3 +1];
    double y3[n3 +1];
    double cx3[n3+ 1];
    double cy3[n3 + 1];
    wypelni(x3, y3, cx3, cy3, n3);

    int n4 = 20;
    double x4[n4 +1];
    double y4[n4 +1];
    double cx4[n4+ 1];
    double cy4[n4 + 1];
    wypelni(x4, y4, cx4, cy4, n4);

    // zad 2
    wypisz(x1, y1, n1);
    wypisz(x2, y2, n2);
    wypisz(x3, y3, n3);
    wypisz(x4, y4, n4);

    // zad 3
    wypiszCzebyszew(cx1, cy1, n1);
    wypiszCzebyszew(cx2, cy2, n2);
    wypiszCzebyszew(cx3, cy3, n3);
    wypiszCzebyszew(cx4, cy4, n4);

     //punkty dla gnuplot
    // wypiszXY(x1, y1, n1);
    // wypiszXY(x2, y2, n2);
    // wypiszXY(x3, y3, n3);
    // wypiszXY(x4, y4, n4);
    // wypiszXY(cx1, cy1, n1);
    // wypiszXY(cx2, cy2, n2);
    // wypiszXY(cx3, cy3, n3);
    // wypiszXY(cx4, cy4, n4);



    return 0;
}