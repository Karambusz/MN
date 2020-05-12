#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 2


double funkcjaF(double x, double y){
    return x*x - 4*x + 8 + y*y - 4*y + x*y;
}

double funkcjaG(double x, double y){
    return (funkcjaF(x,y) - 8);
}

double pochodnaX(double x, double y, double deltaX){
    return (funkcjaG(x + deltaX, y) - funkcjaG(x - deltaX, y)) / (2*deltaX);
}

double pochodnaY(double x, double y, double deltaY){
    return (funkcjaG(x, y + deltaY) - funkcjaG(x, y - deltaY)) / (2*deltaY);    
}

void iloczynMatVec(double matrix[N][N], double vector[N], double result[N], double omega) {
    for(int i = 0; i < N; i++){
        result[i] = 0.0;
        for(int j = 0; j < N; j++) {
            result[i] += matrix[i][j] * vector[j]; 
        }
        result[i]*=omega;
    }
}

double modulVec(double a[N], double b[N]){
    double cx = a[0] - b[0];
    double cy = a[1] - b[1];
    return sqrt ( (pow(cx, 2) + pow(cy, 2)) );

}


void newton(double macierz[N][N], double wektorR[N], double xstart, double ystart, double omega){
    int k = 0;
    double tmp[N];
    double wektorR1[N];
    double gradient[N];
    wektorR[0] = xstart;
    wektorR[1] = ystart;
    wektorR1[0] = wektorR1[1] = 0.0;
    gradient[0] = gradient[1] = 0.0;
    for(int i = 1; i<10000; i++){
        gradient[0] = pochodnaX(wektorR[0], wektorR[1], 0.01);
        gradient[1] = pochodnaY(wektorR[0], wektorR[1], 0.01);
        iloczynMatVec(macierz, gradient, tmp, omega);
        wektorR1[0] = wektorR[0] - tmp[0];
        wektorR1[1] = wektorR[1] - tmp[1];
        k=i;
        if( modulVec(wektorR1, wektorR) < pow(10,-6)){
            break;
        }
        wektorR[0] = wektorR1[0];
        wektorR[1] = wektorR1[1];
    }
    printf("Liczba iteracji = %d, [xmin, ymin] = %g %g \n",k, wektorR1[0], wektorR1[1]);
}

int main(void) {

    double A[N][N];
    double A_odwrotna[N][N];
    double b[N];
    double r[N];

    b[0] = b[1] = -4;
    A[0][0] = A[1][1] = 2;
    A[0][1] = A[1][0] = 1;

    // zadanie 2
    double det = (A[0][0] * A[1][1]) - (A[0][1] * A[1][0]);

    printf("Minimum znalezione bezpośrednio: r_min = ");
    for(int i = 0; i < N; i++){
        r[i] = 0.0;
        for(int j = 0; j < N; j++){
            A_odwrotna[i][j] = (1 / det) * A[i][j]; 
            if( (i==0 && j==1) || (i==1 && j==0))
                A_odwrotna[i][j] = (1 / det) * -A[i][j];
            r[i]+=-A_odwrotna[i][j] * b[j];
        }
        printf("%g ", r[i]);
    }
    printf("\n");
    printf("\n");
    //zadanie 3 
    newton(A_odwrotna, r, 0.0, 0.0, 1.0);
    newton(A_odwrotna, r, 10.0, -10.0, 1.0);
    newton(A_odwrotna, r, 100.0, 100.0, 1.0);
    newton(A_odwrotna, r, 500.0, 500.0, 1.0);
    printf("\n");
    //zadanie 4
    newton(A_odwrotna, r, 10.0, 10.0, 0.1);
    newton(A_odwrotna, r, 10.0, 10.0, 0.4);
    newton(A_odwrotna, r, 10.0, 10.0, 0.7);

    return 0;
}