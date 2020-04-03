#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n 7
#define IT_MAX 12

void iloczynMatVec(double matrix[n][n], double vector[n], double result[n]) {
    for(int i = 0; i < n; i++){
        result[i] = 0.0;
        for(int j = 0; j < n; j++) {
            result[i] += matrix[i][j] * vector[j]; 
        }
    }
}

double iloczynSkalarny(double vector1[n], double vector2[n]) {
    double result = 0.0;
    for(int i = 0; i < n; i++) {
        result += vector1[i] * vector2[i];
    }
    return result;
}



void ilorazVectorSkalar(double vector1[n],  double vector2[n]) {
    for(int i = 0; i < n; i++){
        vector2[i] = vector1[i]/sqrt(iloczynSkalarny(vector1, vector1));
    }
}

void iloczynTensorowy(double result[n][n], double vector[n], double lambda) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++){
            result[i][j] = lambda * vector[i] * vector[j];
        }
    }
}

void roznicaMacierz(double result[n][n], double macierz1[n][n], double macierz2[n][n]) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++){
            result[i][j] = macierz1[i][j] - macierz2[i][j];
        }
    }   
}

void copyMatrix(double macierz1[n][n], double macierz2[n][n]) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++){
            macierz1[i][j] = macierz2[i][j];
        }
    }
}

void copyVectorToMatrix(double result[n][n], double vector[n], int k) {
    for(int i = 0; i < n; i++) {
            result[i][k] = vector[i];
        }
}

void iloczynMatMat(double result[n][n], double macierz1[n][n], double macierz2[n][n]) {
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            result[i][j] = 0.0; 
            for (int k = 0; k < n; k++)
                result[i][j]+=macierz1[i][k] * macierz2[k][j];
        }
    }
}

void tranpose(double macierz1[n][n], double macierz2[n][n]) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++){
            macierz1[j][i] = macierz2[i][j];
        }
    }
}

void printMatrix(double matrix[n][n]) {
    printf("\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j ++) {
            printf("%12g ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void) {

    double A[n][n];
    double W[n][n];
    double Wn[n][n];
    double temp[n][n];
    double X[n][n];
    double XT[n][n];
    double D[n][n];

    // zadanie 1
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            A[i][j] = 1/sqrt(2+abs(i-j));
            W[i][j] = A[i][j];
            Wn[i][j] = A[i][j];
        }
    }
    // zadanie 2
    double xn[n];
    for(int k = 0; k < n; k++) {
       double xk[n] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
       double lambda = 0.0;
       for(int i = 1; i <= IT_MAX; i++){
            iloczynMatVec(W, xk, xn);
            lambda =  iloczynSkalarny(xn, xk)/iloczynSkalarny(xk, xk);
            //printf("%d %f \n",i, lambda); // gnuplot
            ilorazVectorSkalar(xn, xk);
       }
       printf("\n \n");
        iloczynTensorowy(temp, xk, lambda);
        roznicaMacierz(Wn, W, temp);
        copyMatrix(W, Wn);
        copyVectorToMatrix(X, xk, k);
        
        printf("Lambda %d = %f \n", k, lambda);
    }
    printf("Wektory wlasne(kolumna - wektor): \n");
    printMatrix(X);

    // zadanie 3
    iloczynMatMat(temp, A, X);
    tranpose(XT, X);
    iloczynMatMat(D, XT, temp);
    printf("Macierz D: \n");
    printMatrix(D);
    return 0;
}

