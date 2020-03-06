#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "nrutil.h"
#include "nrutil.c"
#include "ludcmp.c"
#include "lubksb.c"




void print_matrix(float** Matrix, const int N) //wyswietla macierze
{
	int i,j;
	printf("\n");
	for(i = 1; i <=N; i++)
	{
		for(j = 1; j <= N; j++)
		{
			printf("%.10f ", Matrix[i][j]);
		}
		printf("\n");
	}	
}

float norma(float** Matrix, const int N) { // norma macierzy
    float max = fabs(Matrix[1][1]);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            if(fabs(Matrix[i][j]) >= max)
                max = fabs(Matrix[i][j]);
       }
   }
   
    return max;
}

int main(void) {
    const int n = 4;
    float **A, **A_copy, **A_odwrotna, **iloczyn, *b, d;
    float det_a = 1.0;
    float norma_a = 1.0;
    float norma_mac_odw = 1.0;
    float wskaznik = 1.0;

    int *indx;
    b = vector(1, n);
    indx = ivector(1, n);
    A = matrix(1, n, 1, n);
    A_copy = matrix(1, n, 1, n);
    A_odwrotna = matrix(1, n, 1, n);
    iloczyn = matrix(1, n, 1, n);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            A[i][j] = 1./(i+j);
            A_copy[i][j] = 1./(i+j);
        }
    }
    printf("Macierz A: \n");
    print_matrix(A,n);

    // zadanie 1
    ludcmp(A_copy, n, indx, &d);

    printf("\nMacierz LU: \n");
    print_matrix(A_copy,n);

    // zadanie 2
	for(int i = 1; i <= n; i++) {
		det_a *= A_copy[i][i];
	}

    printf("\nWyznacznik macierzy: \n");
    printf("%e \n", det_a);

    //zadanie 3

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++) {
            b[j] = 0.0;
        }
        b[i] = 1.0;
        lubksb(A_copy, n, indx, b);
        for(int k = 1; k <= n; k++)
            A_odwrotna[k][i] = b[k];
    }



    printf("\nMacierz A^-1: \n");
    print_matrix(A_odwrotna, n);

    // zadanie 4
    printf("\nIloczyn A*A^-1: \n");

    for (int i = 1; i <= n; i ++){
        for (int j = 1; j <= n; j ++){
            iloczyn[i][j] = 0.; 
            for (int k = 1; k <= n; k++)
                iloczyn[i][j]+=A[i][k] * A_odwrotna[k][j];
            }
        }

    print_matrix(iloczyn, n);
    printf("\n Norma: \n");
    
    
    // zadanie 5
    printf("\n Norma macierzy A: \n");
    norma_a *= norma(A, n);
    printf("%f \n", norma_a);
    
    printf("\n Norma macierzy A^-1: \n");
    norma_mac_odw *= norma(A_odwrotna, n);
    printf("%f \n", norma_mac_odw);
    
    printf("\n wskaznik uwarunkowania: \n");
    wskaznik = norma_a * norma_mac_odw;
    printf("%f \n", wskaznik);

    free_vector(b, 1, n);
    free_ivector(indx, 1, n);
    free_matrix(A, 1, n, 1, n);
    free_matrix(A_copy, 1, n, 1, n);
    free_matrix(A_odwrotna, 1, n, 1, n);
    free_matrix(iloczyn, 1, n, 1, n);

return 0;
}

