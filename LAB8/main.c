#include <stdio.h>
#include <math.h>
#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>


const double xmin = -5.0;
const double xmax = 5.0;
const double alfa = 0.0;
const double beta = 0.0;

double funkcja(double x) {
    return 1/(1 + x*x);
}

double pochodna(double x, double sigma){
    return (funkcja(x - sigma) - 2*funkcja(x) + funkcja(x + sigma)) / (sigma * sigma);
}

double funkcjaCos(double x) {
    return cos(2*x);
}

double delta(int n){
    return (xmax - xmin) / (double)(n-1);
}

double wyliczH(double x, double x1){
    return (x1 - x);
}

double wyliczD(double h, double h1, double y, double y1, double y2){
    return (6.0 / (h + h1)) * ( (y2 - y1)/h1 - (y1 - y)/h);
}

double wyliczA(double y, double y1, double h, double m, double m1){
    return ((y1 - y) / h) - (h/6.0)*(m1 - m); 
}

double wyliczB(double y, double h, double m){
    return y - m * ((h*h)/6.0); 
}

void wypelni(double *x, double *y, double *cosx, double *cosy,int n){
    for (int i = 0; i < n; i++){
        x[i] = y[i] = cosx[i] = cosy[i] = 0.0;
        x[i] = xmin + delta(n)*i;
        y[i] = funkcja(x[i]);
        cosx[i] = xmin + delta(n)*i;
        cosy[i] = funkcjaCos(cosx[i]);
    }
}

void wyznacz_M(double *x, double *y, double *m, int n, double alfa, double beta){
    gsl_matrix *A = gsl_matrix_calloc(n ,n);
    gsl_vector * d = gsl_vector_calloc(n);
    double lambda[n-2];
    double miu[n-2];
    //wypelnienie wektora d
    gsl_vector_set(d, 0, alfa);
    gsl_vector_set(d, n-1, beta);
    for(int i = 1; i < n-1; i++){
        double h = wyliczH(x[i-1], x[i]);
        double h1 = wyliczH(x[i], x[i+1]);
        gsl_vector_set(d, i, wyliczD(h, h1, y[i-1], y[i], y[i+1]));
    }
    //wypelnienie macierzy A
    gsl_matrix_set(A, 0, 0, 1.0);
    gsl_matrix_set(A, n-1, n-1, 1.0);
    for(int i = 1; i < n-1; i++){
        gsl_matrix_set(A, i, i, 2.0);   
    }

    for(int i = 2; i < n; i++){
        double h = wyliczH(x[i-2], x[i-1]);
        double h1 = wyliczH(x[i-1], x[i]); 
        lambda[i-2] =  h1/(h+h1);
        gsl_matrix_set(A, i-1, i, lambda[i-2]);
    }

    for(int i = 0; i < n - 2; i++){
        miu[i] = 1.0 - lambda[i];
        gsl_matrix_set(A, i+1, i, miu[i]);
    }
    // transformacja Householdera
    gsl_linalg_HH_svx(A, d);
    for(int i = 0; i < n; i++){
        m[i] = gsl_vector_get(d, i);
    }

    gsl_vector_free(d);
    gsl_matrix_free(A);
}

double wyznacz_Sx(double *x, double *y, double *m, int n, double xZnaczenia){

    int i = 0;
    for(int j = 1; j < n; j++){
        if(xZnaczenia >= x[j-1] && xZnaczenia <= x[j]){
            i = j;
            break;
        }
    }

    double h = wyliczH(x[i-1], x[i]);
    double s = m[i-1]*( pow((x[i] - xZnaczenia), 3) / (6.0 * h)) +
               m[i]*( pow((xZnaczenia - x[i-1]), 3) / (6.0 * h)) +
               wyliczA(y[i-1], y[i], h, m[i-1], m[i]) * (xZnaczenia - x[i-1]) +
               wyliczB(y[i-1], h, m[i-1]);
            
    return s;
}

void wypisz(double *x, double *y, double *m, int n) {
    for(int i = 0; i<=1000; i++) {
        double xZnaczenia = xmin + 0.01 * i;
        double s = wyznacz_Sx(x, y, m, n, xZnaczenia);        
        printf("%g %g\n",xZnaczenia, s);
    }
    printf("\n\n");
}

void wypiszXY(double *x, double *y, int n) {
    for(int i = 0; i < n; i++) {
        printf("%g %g \n", x[i], y[i]);
    }
    printf("\n \n");
}


int main(void) {
    int n1 = 5;
    double x1[n1];
    double y1[n1];
    double m1[n1];
    double cosx1[n1];
    double cosy1[n1];
    double cosm1[n1];
    wypelni(x1, y1, cosx1, cosy1, n1);
    wyznacz_M(x1, y1, m1, n1, alfa, beta);
    wyznacz_M(cosx1, cosy1, cosm1, n1, alfa, beta);


    int n2 = 8;
    double x2[n2];
    double y2[n2];
    double m2[n2];
    double cosx2[n2];
    double cosy2[n2];
    double cosm2[n2];
    wypelni(x2, y2, cosx2, cosy2, n2);
    wyznacz_M(x2, y2, m2, n2, alfa, beta);
    wyznacz_M(cosx2, cosy2, cosm2, n2, alfa, beta);

    int n3 = 21;
    double x3[n3];
    double y3[n3];
    double m3[n3];
    double cosx3[n3];
    double cosy3[n3];
    double cosm3[n3];
    wypelni(x3, y3, cosx3, cosy3, n3);
    wyznacz_M(x3, y3, m3, n3, alfa, beta);
    wyznacz_M(cosx3, cosy3, cosm3, n3, alfa, beta);

    //wypisywanie dla funkcji(1)
    wypisz(x1, y1, m1, n1);
    wypisz(x2, y2, m2, n2);
    wypisz(x3, y3, m3, n3);

    //wypisywanie dla funkcji(2)
    wypisz(cosx1, cosy1, cosm1, n1);
    wypisz(cosx2, cosy2, cosm2, n2);
    wypisz(cosx3, cosy3, cosm3, n3);

    //punkty dla gnuplot
    // wypiszXY(x1, y1, n1);
    // wypiszXY(x2, y2, n2);
    // wypiszXY(x3, y3, n3);
    // wypiszXY(cosx1, cosy1, n1);
    // wypiszXY(cosx2, cosy2, n2);
    // wypiszXY(cosx3, cosy3, n3);


    //zadanie 5
    int n5 = 10;
    double sigma = 0.01;
    double x5[n5];
    double y5[n5];
    double m5[n5];
    double rozm5[n5];
    for (int i = 0; i < n5; i++){
        x5[i] = y5[i] = rozm5[i] = 0.0;
        x5[i] = xmin + delta(n5)*i;
        y5[i] = funkcja(x5[i]);
        rozm5[i] = pochodna(x5[i], sigma);
    }
    wyznacz_M(x5, y5, m5, n5, alfa, beta);

    for(int i = 0; i < n5; i++){
        printf("x[%d] = %9g m[%d] = %9g rozm[%d] = %9g \n",i, x5[i], i, m5[i], i, rozm5[i]);
    }

    return 0;
}
