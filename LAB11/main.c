#include <stdio.h>
#include <math.h>
#include <time.h>
#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>
#include </usr/include/gsl/gsl_errno.h>
#include </usr/include/gsl/gsl_fft_complex.h>

double funkcja(int N, int i){
    double omega = 2 * ( (2 * M_PI) / (N));
    double funkcja = sin(omega * i) + sin(2 * omega * i) + sin(3 * omega * i);
    double szum = 2 * (rand() / (RAND_MAX + 1.0)) - 1;
    return (funkcja+szum);
}

void wypelni(double *y, int n, FILE *file){
    for(int i = 0; i < n; i++){
        y[2*i] = funkcja(n, i);
        y[2*i + 1] = 0.0;
        fprintf(file, "%d %e \n",i, y[2*i]);
    }
    fprintf(file, "\n\n");
}

void szukajMax(double *y, int n, double ymax){
    static int licznik = 8;
    double module = 0.0;
    for(int i = 0; i < n; i++){
        module = sqrt((pow(y[2*i], 2) +pow(y[2*i+1],2 )));
        if(ymax < module){
            ymax = module;
        }
    }

    for(int i = 0; i < n; i++){
        module = sqrt((pow(y[2*i], 2) +pow(y[2*i+1],2 )));
        if(module < (ymax/2)){
        y[2*i] = 0.0;
        y[2*i + 1] = 0.0;            
        }
    }
    printf("ymax dla k = %d: %g \n",licznik, ymax);
    licznik+=2;
}
void unormowanie(double *y, int n, FILE *file){
    for(int i = 0; i < n; i++){
        y[2*i] /=n;
        y[2*i + 1] /=n;
        fprintf(file, "%d %e \n",i, y[2*i]);         
    }
}

int main(void) {
    FILE *file1;
	file1 = fopen("y8.dat", "w");
    FILE *file2;
	file2 = fopen("y10.dat", "w");
    FILE *file3;
	file3 = fopen("y12.dat", "w");
    FILE *file4;
	file4 = fopen("fft8.dat", "w");
    const int k1 = 8;
    const int k2 = 10;
    const int k3 = 12;
    const int n1 = pow(2,k1);
    const int n2 = pow(2,k2);
    const int n3 = pow(2,k3);
    double y1[2*n1];
    double y2[2*n2];
    double y3[2*n3];
    // zadanie 1
    wypelni(y1, n1, file1);
    wypelni(y2, n2, file2);
    wypelni(y3, n3, file3);
    //zadanie 2
    gsl_fft_complex_radix2_forward(y1, 1, n1);
    gsl_fft_complex_radix2_forward(y2, 1, n2);
    gsl_fft_complex_radix2_forward(y3, 1, n3);
    //zadanie 3
    for(int i = 0; i < n1; i++){
        fprintf(file4, "%d %e %e\n",i, y1[2*i], y1[2*i + 1]);
    }
    //zadanie 4
    double ymax1 = 0.0;
    double ymax2 = 0.0;
    double ymax3 = 0.0;
    szukajMax(y1, n1, ymax1);
    szukajMax(y2, n2, ymax2);
    szukajMax(y3, n3, ymax3);
    //zadanie 5
    gsl_fft_complex_radix2_backward(y1, 1, n1);
    gsl_fft_complex_radix2_backward(y2, 1, n2);
    gsl_fft_complex_radix2_backward(y3, 1, n3);
    unormowanie(y1, n1, file1);
    unormowanie(y2, n2, file2);
    unormowanie(y3, n3, file3);

    fclose(file1);
    fclose(file2);
    fclose(file3);
    fclose(file4);

    return 0;
}