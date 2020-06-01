#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n 8


double funkcja(double x){
    return log(x*x*x + 3*x*x + x + 0.1)*sin(18*x);
}

double odleglosc_trapez(double a, int j, double h){
    return (a + (j+1)*h);
}

double odleglosc(double a, int j, double h){
    return (a + j*h); 
}

void trapezy(double D[n+1][n+1], double a, double b){
    double x = 0.0;
    double x1 = 0.0;
    double h = 0.0;
    int N = 0;

    for(int i = 0; i<=n; i++){
        x = a;
        h = (b - a) / pow(2, i);
        N = pow(2, i);
        double suma = 0.0;
        for(int j = 0; j < N; j++){
            x1 = odleglosc_trapez(a, j, h);
            suma += (h/2)*(funkcja(x) + funkcja(x1));
            x = x1;
        }
        D[i][0] = suma;
    }

    for(int i = 1; i <=n; i++){
        for(int j = 1; j<=i; j++){
            D[i][j] = ( (pow(4,j) * D[i][j-1]) - D[i-1][j-1] ) / ( pow(4,j) - 1);
        }
    }

    // for(int i = 0; i <= n; i++){
    //         printf("w = %d   D_w_0 = %15.10g     D_w_w = %15.10g\n",i, D[i][0], D[i][i]);
    // }
    for(int i = 0; i <= n; i++){
        for(int j = 0; j<=i; j++){
            printf("%12.10g ",D[i][j]);
        }
        printf("\n");
    }
    printf("\n \n");
}

void trzy_osme(double D[n+1][n+1], double a, double b){
    double x = 0.0;
    double x1 = 0.0;
    double x2 = 0.0;
    double x3 = 0.0;
    double h = 0.0;
    int N = 0;
    for(int i = 0; i <=n; i++){
        x = a;
        h = (b-a) / (3 * pow(2,i));
        N = 3 * pow(2,i);
        double suma = 0.0;
        for(int j = 0; j < (N/3); j++){
            x = odleglosc(a, 3*j, h);
            x1 = odleglosc(a, 3*j+1, h);
            x2 = odleglosc(a, 3*j+2, h);
            x3 = odleglosc(a, 3*j+3, h);
            suma += ((3*h)/8) * (funkcja(x) + 3*funkcja(x1) + 3*funkcja(x2) + funkcja(x3));
        }
        D[i][0] = suma;
    }

    for(int i = 1; i <=n; i++){
        for(int j = 1; j<=i; j++){
            D[i][j] = ( (pow(4,j) * D[i][j-1]) - D[i-1][j-1] ) / ( pow(4,j) - 1);
        }
    }

    // for(int i = 0; i <= n; i++){
    //     printf("w = %d   D_w_0 = %15.10g     D_w_w = %15.10g\n",i, D[i][0], D[i][i]);
    // }
    for(int i = 0; i <= n; i++){
        for(int j = 0; j<=i; j++){
            printf("%12.10g ",D[i][j]);
        }
        printf("\n");
    }
    printf("\n \n");
    
}

int main(void) {


    const double a = 0;
    const double b = 1;

    double D[n+1][n+1];
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            D[i][j] = 0.0;
        }
    }
    trapezy(D, a, b);

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            D[i][j] = 0.0;
        }
    }
    trzy_osme(D, a, b);
    return 0;
}